<?php
session_start();
require_once __DIR__ . '/../config.php';
require_once __DIR__ . '/../Database/DBconn.php';
use Database\DBconn;

$config = require __DIR__ . '/../Database/databaseConfig.php';
$db = DBconn::getDB($config);

$product = null;
$colors = [];

if (isset($_GET['id'])) {
    $id = intval($_GET['id']);

    // Recupero prodotto
    $stmt = $db->prepare("SELECT id, name, description, price, image FROM products WHERE id = ?");
    $stmt->execute([$id]);
    $product = $stmt->fetch();

    // Recupero colori associati
    if ($product) {
        $stmtColors = $db->prepare("SELECT color_hex FROM product_colors WHERE product_id = ?");
        $stmtColors->execute([$product->id]);
        $colors = $stmtColors->fetchAll();
    }
}

require_once __DIR__ . '/../Components/header.php';
?>

<main class="container my-5">
    <?php if (!empty($_SESSION['success'])): ?>
        <div class="alert alert-success text-center">
            <?= htmlspecialchars($_SESSION['success']) ?>
        </div>
        <?php unset($_SESSION['success']); ?>
    <?php endif;
    if ($product): ?>
        <div class="row">
            <div class="col-md-6">
                <img src="<?= htmlspecialchars(BASE_URL . '/' . $product->image) ?>" alt="Prodotto" class="img-fluid rounded">
            </div>
            <div class="col-md-6">
                <h1 class="mb-3"><?= htmlspecialchars($product->name) ?></h1>
                <p class="mb-4"><?= htmlspecialchars($product->description) ?></p>
                <p class="h4 text-danger mb-4">€ <?= number_format($product->price, 2) ?></p>

                <form method="POST" action="<?= BASE_URL ?>/Cart/add_to_cart.php">
                    <input type="hidden" name="product_id" value="<?= $product->id ?>">

                    <div class="d-flex align-items-center mb-3">
                        <button type="button" class="btn btn-outline-secondary" id="decrease-qty">-</button>
                        <input type="number" id="product-quantity" name="quantity" class="form-control text-center mx-1 w-25" value="1" min="1" max="100">
                        <button type="button" class="btn btn-outline-secondary" id="increase-qty">+</button>
                    </div>

                    <!-- Selezione Colore Dinamica -->
                    <?php if (!empty($colors)): ?>
                        <div class="mb-3">
                            <label class="form-label">Seleziona il colore:</label>
                            <div id="color-options" class="d-flex flex-wrap gap-3">
                                <?php foreach ($colors as $index => $color): ?>
                                    <?php
                                    $colorHex = htmlspecialchars($color->color_hex);
                                    $idAttr = "color-" . strtolower(str_replace('#', '', $colorHex));
                                    ?>
                                    <div class="form-check me-2">
                                        <input class="form-check-input" type="radio" name="color" id="<?= $idAttr ?>" value="<?= $colorHex ?>" <?= $index === 0 ? 'checked' : '' ?>>
                                        <label class="form-check-label d-flex align-items-center gap-1" for="<?= $idAttr ?>">
                                            <span class="rounded-circle border" style="display:inline-block;width:20px;height:20px;background-color:<?= $colorHex ?>"></span>
                                        </label>
                                    </div>
                                <?php endforeach; ?>
                            </div>
                        </div>
                    <?php endif; ?>

                    <?php if (isset($_SESSION['user_id'])): ?>
                        <button type="submit" class="btn btn-primary btn-lg">Aggiungi al Carrello</button>
                    <?php else: ?>
                        <a href="<?= BASE_URL ?>/Login/login.php" class="btn btn-outline-primary btn-lg">Accedi per acquistare</a>
                    <?php endif; ?>
                </form>
            </div>
        </div>
    <?php else: ?>
        <div class="alert alert-warning text-center">
            Prodotto non trovato.
        </div>
    <?php endif; ?>
</main>

<?php require_once __DIR__ . '/../Components/footer.php'; ?>

<script>
    const decreaseBtn = document.getElementById('decrease-qty');
    const increaseBtn = document.getElementById('increase-qty');
    const qtyInput = document.getElementById('product-quantity');

    if (decreaseBtn && increaseBtn && qtyInput) {
        decreaseBtn.addEventListener('click', () => {
            let value = parseInt(qtyInput.value, 10);
            if (value > 1) qtyInput.value = value - 1;
        });
        increaseBtn.addEventListener('click', () => {
            let value = parseInt(qtyInput.value, 10);
            qtyInput.value = value + 1;
        });
    }
</script>
