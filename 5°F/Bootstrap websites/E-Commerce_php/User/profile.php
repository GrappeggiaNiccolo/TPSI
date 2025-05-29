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

$userId = $_SESSION['user_id'];

// Recupero dati utente
$stmt = $db->prepare("SELECT username, email, created_at FROM users WHERE id = ?");
$stmt->execute([$userId]);
$user = $stmt->fetch();

// Gestione eliminazione account
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['delete_account'])) {
    $stmt = $db->prepare("DELETE FROM users WHERE id = ?");
    $stmt->execute([$userId]);

    session_destroy();
    header("Location: " . BASE_URL . "/index.php?account_deleted=1");
    exit;
}

// Recupero ordini
$stmtOrders = $db->prepare("SELECT id, total, status, created_at FROM orders WHERE user_id = ? ORDER BY created_at DESC");
$stmtOrders->execute([$userId]);
$orders = $stmtOrders->fetchAll();

require_once __DIR__ . '/../Components/header.php';
?>

<main class="container my-5">
    <h1 class="mb-4 text-center">Profilo Utente</h1>

    <?php if ($user): ?>
        <div class="card p-4 shadow-sm mb-5">
            <h5>Username: <?= htmlspecialchars($user->username) ?></h5>
            <p>Email: <?= htmlspecialchars($user->email) ?></p>
            <p>Registrato il: <?= date("d/m/Y", strtotime($user->created_at)) ?></p>

            <form method="POST" onsubmit="return confirm('Sei sicuro di voler eliminare il tuo account?');">
                <button type="submit" name="delete_account" class="btn btn-danger mt-3">Elimina Account</button>
            </form>
        </div>
    <?php endif; ?>

    <h2 class="mb-3">I tuoi ordini</h2>

    <?php if ($orders): ?>
        <div class="table-responsive">
            <table class="table table-striped table-hover align-middle">
                <thead class="table-dark">
                <tr>
                    <th># Ordine</th>
                    <th>Data</th>
                    <th>Totale</th>
                    <th>Stato</th>
                </tr>
                </thead>
                <tbody>
                <?php foreach ($orders as $order): ?>
                    <tr>
                        <td><?= htmlspecialchars($order->id) ?></td>
                        <td><?= date("d/m/Y H:i", strtotime($order->created_at)) ?></td>
                        <td>€ <?= number_format($order->total, 2, ',', '.') ?></td>
                        <td><?= htmlspecialchars(ucfirst($order->status)) ?></td>
                    </tr>
                <?php endforeach; ?>
                </tbody>
            </table>
        </div>
    <?php else: ?>
        <div class="alert alert-info">Non hai ancora effettuato ordini.</div>
    <?php endif; ?>
</main>

<?php require_once __DIR__ . '/../Components/footer.php'; ?>
