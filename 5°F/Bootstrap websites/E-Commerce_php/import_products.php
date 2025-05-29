<?php
require_once __DIR__ . '/config.php';
session_start();
require_once __DIR__ . '/Database/DBconn.php';
$config = require __DIR__ . '/Database/databaseConfig.php';
use Database\DBconn;
$db = DBconn::getDB($config);

$jsonString = file_get_contents(__DIR__ . '/data/data.json');
$data = json_decode($jsonString, true);

if (!$data) {
    die("Errore nella decodifica del file JSON");
}

$products = $data['archive']['products'] ?? [];

if (empty($products)) {
    die("Nessun prodotto trovato nel JSON");
}

// Preparo le query
$insertBrandStmt = $db->prepare("INSERT INTO brands (name) VALUES (:name)");
$selectBrandStmt = $db->prepare("SELECT id FROM brands WHERE name = :name");

$insertProductStmt = $db->prepare("
    INSERT INTO products (id, name, full_name, description, price, image, stock, brand_id)
    VALUES (:id, :name, :full_name, :description, :price, :image, :stock, :brand_id)
");

$insertColorStmt = $db->prepare("
    INSERT INTO product_colors (product_id, color_hex)
    VALUES (:product_id, :color_hex)
");

foreach ($products as $product) {
    // Trova o inserisci brand
    $selectBrandStmt->execute([':name' => $product['brand']]);
    $brandId = $selectBrandStmt->fetchColumn();

    if (!$brandId) {
        $insertBrandStmt->execute([':name' => $product['brand']]);
        $brandId = $db->lastInsertId();
    }

    // Converti prezzo da stringa "400 €" a float 400.00
    $price = floatval(str_replace(['€', ' '], '', $product['price']));

    // Inserisci prodotto (se vuoi puoi gestire già prodotti esistenti con UPDATE)
    $insertProductStmt->execute([
        ':id' => $product['id'],
        ':name' => $product['name'],
        ':full_name' => $product['full-name'],
        ':description' => $product['description'],
        ':price' => $price,
        ':image' => $product['image'],
        ':stock' => $product['stock'],
        ':brand_id' => $brandId
    ]);

    // Inserisci colori
    foreach ($product['colors'] as $colorHex) {
        $insertColorStmt->execute([
            ':product_id' => $product['id'],
            ':color_hex' => $colorHex
        ]);
    }
}

echo "Import dati completato con successo.\n";
