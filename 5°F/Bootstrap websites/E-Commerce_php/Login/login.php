<?php
session_start();
require_once __DIR__ . '/../config.php';
require_once __DIR__ . '/../Database/DBconn.php';
use Database\DBconn;

$config = require __DIR__ . '/../Database/databaseConfig.php';
$db = DBconn::getDB($config);

$errors = [];

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $email = trim($_POST['email'] ?? '');
    $password = $_POST['password'] ?? '';

    if (empty($email) || empty($password)) {
        $errors[] = "Inserisci sia email che password.";
    } else {
        $stmt = $db->prepare("SELECT id, username, password FROM users WHERE email = :email");
        $stmt->execute([':email' => $email]);
        $user = $stmt->fetch();

        if ($user && password_verify($password, $user->password)) {
            // Login riuscito
            $_SESSION['user_id'] = $user->id;
            $_SESSION['username'] = $user->username;

            header("Location: " . BASE_URL . "/index.php");
            exit;
        } else {
            $errors[] = "Credenziali non valide.";
        }
    }
}
?>

<?php require_once __DIR__ . '/../Components/header.php'; ?>

<main class="container my-5" style="max-width: 500px;">
    <h1 class="mb-4">Accedi</h1>

    <?php if (!empty($errors)): ?>
        <div class="alert alert-danger">
            <?php foreach ($errors as $error): ?>
                <div><?= htmlspecialchars($error) ?></div>
            <?php endforeach; ?>
        </div>
    <?php endif; ?>

    <form method="POST">
        <div class="mb-3">
            <label for="email" class="form-label">Email</label>
            <input type="email" name="email" id="email" class="form-control" required value="<?= htmlspecialchars($_POST['email'] ?? '') ?>">
        </div>

        <div class="mb-3">
            <label for="password" class="form-label">Password</label>
            <input type="password" name="password" id="password" class="form-control" required>
        </div>

        <button type="submit" class="btn btn-primary">Accedi</button>
    </form>

    <p class="mt-3">
        Non hai un account? <a href="<?= BASE_URL ?>/Register/register.php">Registrati qui</a>
    </p>
</main>

<?php require_once __DIR__ . '/../Components/footer.php'; ?>
