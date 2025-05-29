<?php
session_start();
require_once __DIR__ . '/../config.php';
require_once __DIR__ . '/../Database/DBconn.php';
use Database\DBconn;

if (!isset($_SESSION['user_id'])) {
    // Utente non loggato
    header("Location: " . BASE_URL . "/Login/login.php");
    exit;
}

$config = require __DIR__ . '/../Database/databaseConfig.php';
$db = DBconn::getDB($config);

// Validazione input
$userId = $_SESSION['user_id'];
$productId = isset($_POST['product_id']) ? intval($_POST['product_id']) : 0;
$quantity = isset($_POST['quantity']) ? intval($_POST['quantity']) : 1;
$colorHex = isset($_POST['color']) ? trim($_POST['color']) : null;

if ($productId <= 0 || $quantity <= 0 || !$colorHex || !preg_match('/^#[0-9A-Fa-f]{6}$/', $colorHex)) {
    $_SESSION['error'] = "Dati non validi per il carrello.";
    header("Location: " . BASE_URL . "/index.php");
    exit;
}

// Verifica che il prodotto e il colore esistano
$stmt = $db->prepare("SELECT COUNT(*) FROM product_colors WHERE product_id = ? AND color_hex = ?");
$stmt->execute([$productId, $colorHex]);
$colorExists = $stmt->fetchColumn();

if (!$colorExists) {
    $_SESSION['error'] = "Il colore selezionato non è disponibile per questo prodotto.";
    header("Location: " . BASE_URL . "/index.php");
    exit;
}

// Verifica se lo stesso prodotto (con lo stesso colore) è già nel carrello
$stmt = $db->prepare("SELECT id, quantity FROM cart WHERE user_id = ? AND product_id = ? AND color_hex = ?");
$stmt->execute([$userId, $productId, $colorHex]);
$existing = $stmt->fetch();

if ($existing) {
    // Aggiorna quantità
    $newQuantity = $existing->quantity + $quantity;
    $updateStmt = $db->prepare("UPDATE cart SET quantity = ? WHERE id = ?");
    $updateStmt->execute([$newQuantity, $existing->id]);
} else {
    // Inserisci nuovo elemento
    $insertStmt = $db->prepare("INSERT INTO cart (user_id, product_id, quantity, color_hex) VALUES (?, ?, ?, ?)");
    $insertStmt->execute([$userId, $productId, $quantity, $colorHex]);
}

$_SESSION['success'] = "Prodotto aggiunto al carrello!";
header("Location: " . BASE_URL . "/Shop/productPage.php?id=" . $productId);
exit;
