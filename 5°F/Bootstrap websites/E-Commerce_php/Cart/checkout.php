<?php
session_start();
require_once __DIR__ . '/../config.php';
require_once __DIR__ . '/../Database/DBconn.php';
use Database\DBconn;

if (!isset($_SESSION['user_id'])) {
    header("Location: " . BASE_URL . "/Login/login.php");
    exit;
}

$userId = $_SESSION['user_id'];
$config = require __DIR__ . '/../Database/databaseConfig.php';
$db = DBconn::getDB($config);

// Recupera prodotti nel carrello
$stmt = $db->prepare("
    SELECT c.id AS cart_id, p.name, p.image, p.price, c.quantity, c.color_hex
    FROM cart c
    JOIN products p ON c.product_id = p.id
    WHERE c.user_id = ?
");
$stmt->execute([$userId]);
$cartItems = $stmt->fetchAll();

$total = 0;
foreach ($cartItems as $item) {
    $total += $item->price * $item->quantity;
}

// Gestione conferma ordine
if ($_SERVER['REQUEST_METHOD'] === 'POST' && !empty($cartItems)) {
    $db->beginTransaction();

    try {
        // Inserisci ordine
        $stmt = $db->prepare("INSERT INTO orders (user_id, total) VALUES (?, ?)");
        $stmt->execute([$userId, $total]);
        $orderId = $db->lastInsertId();

        // Potresti anche salvare i dettagli dell'ordine qui

        // Svuota carrello
        $stmt = $db->prepare("DELETE FROM cart WHERE user_id = ?");
        $stmt->execute([$userId]);

        $db->commit();

        $_SESSION['order_success'] = true;
        header("Location: " . BASE_URL . "/Cart/checkout.php");
        exit;
    } catch (Exception $e) {
        $db->rollBack();
        $error = "Errore durante il checkout. Riprova.";
    }
}

require_once __DIR__ . '/../Components/header.php';
?>

<main class="container my-5">
    <h1 class="mb-4 text-center">Checkout</h1>

    <?php if (isset($_SESSION['order_success'])): ?>
        <div class="alert alert-success text-center">
            Ordine completato con successo!
        </div>
        <?php unset($_SESSION['order_success']); ?>
    <?php elseif (empty($cartItems)): ?>
        <div class="alert alert-warning text-center">
            Il tuo carrello è vuoto.
        </div>
    <?php else: ?>
        <div class="row">
            <div class="col-lg-8">
                <ul class="list-group mb-4">
                    <?php foreach ($cartItems as $item): ?>
                        <li class="list-group-item d-flex justify-content-between align-items-center">
                            <div class="d-flex align-items-center gap-3">
                                <img src="<?= htmlspecialchars(BASE_URL . '/' . $item->image) ?>" width="60" class="rounded" alt="<?= htmlspecialchars($item->name) ?>">
                                <div>
                                    <strong><?= htmlspecialchars($item->name) ?></strong><br>
                                    <small>Quantità: <?= $item->quantity ?></small><br>
                                    <small>Colore: <span style="background-color:<?= $item->color_hex ?>; width: 12px; height: 12px; display:inline-block; border:1px solid #333; border-radius:50%"></span></small>
                                </div>
                            </div>
                            <span>€ <?= number_format($item->price * $item->quantity, 2) ?></span>
                        </li>
                    <?php endforeach; ?>
                </ul>
            </div>
            <div class="col-lg-4">
                <div class="card p-3 shadow-sm">
                    <h4 class="mb-3">Totale: € <?= number_format($total, 2) ?></h4>
                    <?php if (isset($error)): ?>
                        <div class="alert alert-danger"><?= $error ?></div>
                    <?php endif; ?>
                    <form method="POST">
                        <button type="submit" class="btn btn-success w-100">Conferma Ordine</button>
                    </form>
                </div>
            </div>
        </div>
    <?php endif; ?>
</main>

<?php require_once __DIR__ . '/../Components/footer.php'; ?>
