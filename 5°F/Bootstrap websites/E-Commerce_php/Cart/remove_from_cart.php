<?php
session_start();
require_once __DIR__ . '/../config.php';
require_once __DIR__ . '/../Database/DBconn.php';
use Database\DBconn;

if (!isset($_SESSION['user_id'])) {
    header("Location: " . BASE_URL . "/Login/login.php");
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['cart_id'])) {
    $cartId = intval($_POST['cart_id']);
    $userId = $_SESSION['user_id'];

    $config = require __DIR__ . '/../Database/databaseConfig.php';
    $db = DBconn::getDB($config);

    // Assicura che l'elemento appartenga all'utente loggato
    $stmt = $db->prepare("DELETE FROM cart WHERE id = ? AND user_id = ?");
    $stmt->execute([$cartId, $userId]);
}

header("Location: cart.php");
exit;
