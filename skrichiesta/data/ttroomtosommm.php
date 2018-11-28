<?php
/**
 * API per risposta a dispositivo SOMMM per visualizzazione dinamica delle classi in aula/laboratorio
 *
 * @param string $stanza identificativo dell'aula/laboratorio
 *
 * @author @fcucino (17336) 5^Ai 2018/2019
 * @group n.1 Annunziata Victor - Bussola Riccardo - Cucino Federico
 */

date_default_timezone_set('Europe/Rome'); // Può servire a classe DateTime usata successivamente

if (!isset($_GET['stanza'])) {
    echo json_encode("Missing parameter 'stanza'");
    http_response_code(403);
    die();
}

/**
 * Converte eventuali caratteri speciali per prevenire SQL Injection
 * @param string $data stringa da elaborare
 * @return string stringa elaborata
 */
function disarmData($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    $data = htmlentities($data);
    $data = str_replace("'", "''", $data);
    return $data;
}

$sqlHost = '';
$sqlUsername = '';
$sqlPassword = '';
$sqlDatabaseName = '';
$conn = new mysqli($sqlHost, $sqlUsername, $sqlPassword, $sqlDatabaseName);
if ($conn->connect_error) {
    http_response_code(503); //Internal Server Error
    die();
}

$stanza = strtoupper(disarmData($_GET['stanza']));

// Query oggi
// Thanks to @mgiacopu and @rtantalo
$sql = "SELECT `giorno_settimana`, `ora`, `stanza`, `risorsa`, `Column 3` AS 'materia', `professore1`, `professore2`
FROM marconitt.timetable
       LEFT JOIN marconitt.GPU001 ON marconitt.timetable.giorno_settimana = marconitt.GPU001.`Column 5`
                                       AND marconitt.timetable.ora = marconitt.GPU001.`Column 6`
                                       AND marconitt.timetable.stanza = marconitt.GPU001.`Column 4`
WHERE `marconitt`.`timetable`.`giorno` = CURDATE()
  AND `marconitt`.`timetable`.`stanza` = '$stanza'
GROUP BY `ora`, `stanza`, `risorsa`, `giorno_settimana`, `professore1`, `professore2`
ORDER BY `ora`;";

$result = $conn->query($sql);
if (!$result) {
    http_response_code(400);
    die();
}

$giorniTxt = ['Domenica', 'Lunedi\'', 'Martedi\'', 'Mercoledi\'', 'Giovedi\'', 'Venerdi\'', 'Sabato'];
$mesiTxt = ['Gennaio', 'Febbraio', 'Marzo', 'Aprile', 'Maggio', 'Giugno', 'Luglio', 'Agosto', 'Settembre', 'Ottobre', 'Novembre', 'Dicembre'];
$giornoTxt = $giorniTxt[date('w')];
$giorno = date('d');
$meseTxt = $mesiTxt[date('n') - 1];
$anno = date('o');

$today = "$giornoTxt, $giorno $meseTxt $anno";

$giornoSet = date('w');

// Ora attuale
$ore = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
$oraTondaNow = date('G');
$oraAttuale = isset($ore[$oraTondaNow - 8]) ? $ore[$oraTondaNow - 8] : 0;
if ($oraTondaNow >= 6 && $oraTondaNow <= 8) $oraAttuale = 1; // Dalle 6:00 simula che sia la prima ora per aggiornare display

/**
 * Taglia una stringa a 16 caratteri complessivi, per questione di spazio fisico sul display
 * @param $str string stringa da tagliare
 * @return string|null
 */
function maxTxtLength($str) {
    if ($str == NULL) return NULL;

    $length = strlen(utf8_decode($str));
    if ($length > 16) {
        $str = substr($str, 0, 15);
        $str .= '.';
    }
    return $str;
}

/**
 * Elabora la query oggi
 * @param $rows mysqli_result result della query
 * @return array
 */
function todayRows($rows) {
    $oggi = array();
    while ($row = $rows->fetch_assoc()) {
        if ($row['risorsa'] != NULL) {
            $o = array(
                'ora' => $row['ora'],
                'prof1' => maxTxtLength(ucwords(strtolower($row['professore1']))), // Prima lettera maiuscola di ogni parola, tagliata a 16 caratteri
                'prof2' => maxTxtLength(ucwords(strtolower($row['professore2']))), // Prima lettera maiuscola di ogni parola, tagliata a 16 caratteri
                'mat' => $row['materia'],
                'res' => $row['risorsa']
            );
        } else { // Se la classe è assente la materia per quell'ora + giorno in GPU001 è comunque presente, quindi null forzato
            $o = array(
                'ora' => $row['ora'],
                'prof1' => null,
                'prof2' => null,
                'mat' => null,
                'res' => null
            );
        }
        array_push($oggi, $o);
    }
    return $oggi;
}

/**
 * Ottiene il lunedì e il sabato di questa settimana
 * @return array
 */
function getWeekStartEnd() {
    $scorsa = new DateTime('last sunday'); // Domenica scorsa
    $scorsa->modify('+1 day'); // Lunedì dopo domenica scorsa
    $prossima = clone($scorsa);
    $prossima->modify('+5 days'); // Sabato successiva a domenica scorsa
    return array(
        'lunedi' => $scorsa->format('Y-m-d'),
        'sabato' => $prossima->format('Y-m-d')
    );
}

$weekStartEnd = getWeekStartEnd();
$lunedi = $weekStartEnd['lunedi'];
$sabato = $weekStartEnd['sabato'];

// Query settimanale
$sqlWeek = "SELECT `giorno_settimana`, `ora`, `stanza`, `risorsa`
FROM marconitt.timetable
       LEFT JOIN marconitt.GPU001 ON marconitt.timetable.giorno_settimana = marconitt.GPU001.`Column 5`
                                       AND marconitt.timetable.ora = marconitt.GPU001.`Column 6`
                                       AND marconitt.timetable.stanza = marconitt.GPU001.`Column 4`
WHERE marconitt.timetable.giorno BETWEEN '$lunedi' AND '$sabato'
    AND marconitt.timetable.stanza = '$stanza'
GROUP BY `giorno_settimana`, `ora`, `stanza`, `giorno_settimana`
ORDER BY `giorno_settimana`, `ora`;";

$resultWeek = $conn->query($sqlWeek);
if (!$resultWeek) {
    http_response_code(400);
    die();
}

/**
 * Elabora la query settimanale
 * @param $rows mysqli_result result della query
 * @return array
 */
function weekRows($rows) {
    $oggi = array();

    while ($row = $rows->fetch_assoc()) {
        $res = $row['risorsa'];
        if (strlen($res) > 3) $res = 'OCC'; // Se attività extra solitamente la descrizione è maggiore di 3 caratteri, quindi 'OCC' per 'OCCUPATO'
        $oggi[$row['giorno_settimana']][$row['ora']] = $res; // La query dovrebbe essere già ordinata per giorno_settimana, ora
    }

    return $oggi;
}

$response = array(
    'stanza' => $stanza,
    'giorno' => $today,
    'giornoSettimana' => intval($giornoSet),
    'oraAttuale' => $oraAttuale,
    'oggi' => todayRows($result),
    'settimana' => weekRows($resultWeek)
);

echo json_encode($response);