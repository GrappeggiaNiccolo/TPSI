<?php
require_once __DIR__ . '/config.php';
session_start();

require_once __DIR__ . '/Database/DBconn.php';
$config = require __DIR__ . '/Database/databaseConfig.php';
use Database\DBconn;

$db = DBconn::getDB($config);

// Recupera 3 prodotti
$stmt = $db->query("
    SELECT id, name, description, price, image
    FROM products
    ORDER BY price DESC
    LIMIT 3
");
$prodotti = $stmt->fetchAll();

require_once __DIR__ . '/Components/header.php';
?>

<!-- Hero Section -->
<section id="hero" class="hero text-center bg-primary text-white py-5">
    <div class="container">
        <?php if(isset($_SESSION['user_id'])): ?>
        <h1 class="display-4">Benvenuto nel nostro web store, <?=$_SESSION['username'];?>!</h1>
        <?php else: ?>
            <h1 class="display-4">Benvenuto nel nostro web store!</h1>
        <?php endif; ?>
        <p class="lead">Scopri i migliori smartphone selezionati per te</p>
    </div>
</section>

<main>
    <div class="container my-5">
        <h1 class="text-center mb-4">Prodotti in evidenza</h1>
        <div class="row" id="cards">
            <?php if ($prodotti): ?>
                <?php foreach ($prodotti as $prodotto): ?>
                    <div class="col-md-4 mb-4">
                        <div class="card h-100">
                            <?php if (!empty($prodotto->image)): ?>
                                <img src="<?= htmlspecialchars(BASE_URL.'/'.$prodotto->image) ?>" class="card-img-top" alt="<?= htmlspecialchars($prodotto->name) ?>">
                            <?php endif; ?>
                            <div class="card-body d-flex flex-column">
                                <h5 class="card-title"><?= htmlspecialchars($prodotto->name) ?></h5>
                                <p class="card-text"><?= htmlspecialchars($prodotto->description) ?></p>
                                <p class="text-danger fw-bold">€ <?= number_format($prodotto->price, 2) ?></p>
                                <a href="<?= BASE_URL ?>/Shop/productPage.php?id=<?= $prodotto->id ?>" class="btn btn-outline-primary mt-auto">Vedi Dettagli</a>
                            </div>
                        </div>
                    </div>
                <?php endforeach; ?>
            <?php else: ?>
                <p class="text-center">Nessun prodotto trovato.</p>
            <?php endif; ?>
        </div>
    </div>
</main>

<?php require_once __DIR__ . '/Components/footer.php'; ?>
