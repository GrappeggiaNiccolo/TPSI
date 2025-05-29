<?php
if(session_status() == PHP_SESSION_NONE) {
    session_start();
}
require_once __DIR__ . '/../config.php';
?>
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <title>E-Commerce</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- Bootstrap 5 CDN -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap-icons/font/bootstrap-icons.css" rel="stylesheet">
    <link rel="stylesheet" href="<?= BASE_URL ?>/style/style.css">
</head>
<body class="d-flex flex-column min-vh-100">
<nav class="navbar navbar-expand-lg navbar-light bg-light border-bottom shadow-sm">
    <div class="container-fluid">
        <a class="navbar-brand nav-link" href="<?= BASE_URL ?>">E-Commerce</a>
        <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNav">
            <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="navbarNav">
            <ul class="navbar-nav me-auto">
                <li class="nav-item"><a href="<?= BASE_URL ?>" class="nav-link">Home</a></li>
                <li class="nav-item"><a href="<?= BASE_URL ?>/Shop/products.php" class="nav-link">Shop</a></li>
            </ul>
            <div class="d-flex align-items-center">
                <?php if (!isset($_SESSION['user_id'])): ?>
                <ul class="navbar-nav me-auto">
                    <li class="nav-item"><a href="<?= BASE_URL ?>/Login/login.php" class="nav-link">Login</a></li>
                    <li class="nav-item"><a href="<?= BASE_URL ?>/Register/register.php" class="nav-link">Registrati</a></li>
                </ul>
                <?php else: ?>
                    <ul class="navbar-nav me-auto">
                        <li class="nav-item"><a href="<?= BASE_URL ?>/User/profile.php" class="nav-link">Profilo</a></li>
                        <li class="nav-item"><a href="<?= BASE_URL ?>/Login/logout.php" class="nav-link">Logout</a></li>
                        <li class="nav-item"><a href="<?= BASE_URL ?>/Cart/cart.php" class="nav-link">Carrello</a></li>
                    </ul>
                <?php endif; ?>
                <button id="bd-theme" class="btn btn-outline-secondary">
                    <i class="bi bi-sun-fill"></i>
                </button>
            </div>
        </div>
    </div>
</nav>
