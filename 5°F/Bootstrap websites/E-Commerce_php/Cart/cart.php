<?php
session_start();
require_once __DIR__ . '/../config.php';
require_once __DIR__ . '/../Database/DBconn.php';
use Database\DBconn;

if (!isset($_SESSION['user_id'])) {
    header("Location: " . BASE_URL . "/Login/login.php");
    exit;
}

$config = require __DIR__ . '/../Database/databaseConfig.php';
$db = DBconn::getDB($config);

// Recupero elementi del carrello
$userId = $_SESSION['user_id'];
$stmt = $db->prepare("
    SELECT 
        cart.id AS cart_id,
        products.id AS product_id,
        products.name,
        products.image,
        products.price,
        cart.quantity,
        cart.color_hex
    FROM cart
    JOIN products ON cart.product_id = products.id
    WHERE cart.user_id = ?
");
$stmt->execute([$userId]);
$cartItems = $stmt->fetchAll();

$total = 0;
foreach ($cartItems as $item) {
    $total += $item->price * $item->quantity;
}

require_once __DIR__ . '/../Components/header.php';
?>

<main class="container my-5">
    <h1 class="text-center mb-4">Il tuo Carrello</h1>

    <?php if (empty($cartItems)): ?>
        <div class="alert alert-info text-center">Il carrello è vuoto.</div>
    <?php else: ?>
        <div class="row">
            <div class="col-lg-8">
                <div class="table-responsive">
                    <table class="table table-bordered table-striped">
                        <thead class="table-primary">
                        <tr>
                            <th>Immagine</th>
                            <th>Prodotto</th>
                            <th>Quantità</th>
                            <th>Prezzo Unitario</th>
                            <th>Totale</th>
                            <th>Rimuovi</th>
                        </tr>
                        </thead>
                        <tbody>
                        <?php foreach ($cartItems as $item): ?>
                            <tr>
                                <td>
                                    <img src="<?= htmlspecialchars(BASE_URL . '/' . $item->image) ?>" alt="Immagine prodotto" width="80">
                                </td>
                                <td>
                                    <?= htmlspecialchars($item->name) ?><br>
                                    <small>Colore: <span style="background-color:<?= htmlspecialchars($item->color_hex) ?>; width:15px; height:15px; display:inline-block; border:1px solid #ccc;"></span></small>
                                </td>
                                <td><?= (int)$item->quantity ?></td>
                                <td>€ <?= number_format($item->price, 2) ?></td>
                                <td>€ <?= number_format($item->price * $item->quantity, 2) ?></td>
                                <td>
                                    <form method="POST" action="remove_from_cart.php">
                                        <input type="hidden" name="cart_id" value="<?= $item->cart_id ?>">
                                        <button type="submit" class="btn btn-sm btn-danger">
                                            <i class="bi bi-trash"></i>
                                        </button>
                                    </form>
                                </td>
                            </tr>
                        <?php endforeach; ?>
                        </tbody>
                    </table>
                </div>
            </div>
            <div class="col-lg-4">
                <div class="card p-3 shadow-sm">
                    <h4 class="fw-bold">Riepilogo</h4>
                    <p class="fs-5">Totale: <strong>€ <?= number_format($total, 2) ?></strong></p>
                    <a href="<?= BASE_URL ?>/Cart/checkout.php" class="btn btn-success w-100">Procedi al pagamento</a>
                </div>
            </div>
        </div>
    <?php endif; ?>
</main>

<?php require_once __DIR__ . '/../Components/footer.php'; ?>
