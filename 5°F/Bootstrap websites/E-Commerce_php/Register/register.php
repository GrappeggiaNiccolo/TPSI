<?php
session_start();
require_once __DIR__ . '/../config.php';
require_once __DIR__ . '/../Database/DBconn.php';
use Database\DBconn;

$config = require __DIR__ . '/../Database/databaseConfig.php';
$db = DBconn::getDB($config);

$errors = [];
$success = false;

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = trim($_POST['username'] ?? '');
    $email = trim($_POST['email'] ?? '');
    $password = $_POST['password'] ?? '';
    $confirm = $_POST['confirm_password'] ?? '';

    // Validazioni base
    if (empty($username) || empty($email) || empty($password) || empty($confirm)) {
        $errors[] = "Tutti i campi sono obbligatori.";
    } elseif (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
        $errors[] = "Email non valida.";
    } elseif ($password !== $confirm) {
        $errors[] = "Le password non coincidono.";
    } elseif (strlen($password) < 6) {
        $errors[] = "La password deve contenere almeno 6 caratteri.";
    }

    if (empty($errors)) {
        // Verifica se utente o email esistono già
        $stmt = $db->prepare("SELECT COUNT(*) FROM users WHERE username = :username OR email = :email");
        $stmt->execute([':username' => $username, ':email' => $email]);
        if ($stmt->fetchColumn() > 0) {
            $errors[] = "Username o email già registrati.";
        } else {
            $hashedPassword = password_hash($password, PASSWORD_DEFAULT);

            $insert = $db->prepare("
                INSERT INTO users (username, email, password) 
                VALUES (:username, :email, :password)
            ");
            $insert->execute([
                ':username' => $username,
                ':email' => $email,
                ':password' => $hashedPassword
            ]);

            $success = true;
        }
    }
}
?>

<?php require_once __DIR__ . '/../Components/header.php'; ?>

<main class="container my-5" style="max-width: 600px;">
    <h1 class="mb-4">Registrazione</h1>

    <?php if (!empty($errors)): ?>
        <div class="alert alert-danger">
            <ul class="mb-0">
                <?php foreach ($errors as $error): ?>
                    <li><?= htmlspecialchars($error) ?></li>
                <?php endforeach; ?>
            </ul>
        </div>
    <?php elseif ($success): ?>
        <div class="alert alert-success">
            Registrazione avvenuta con successo! <a href="<?= BASE_URL ?>/Login/login.php">Accedi ora</a>.
        </div>
    <?php endif; ?>

    <form method="POST">
        <div class="mb-3">
            <label for="username" class="form-label">Username *</label>
            <input type="text" name="username" id="username" class="form-control" required value="<?= htmlspecialchars($_POST['username'] ?? '') ?>">
        </div>

        <div class="mb-3">
            <label for="email" class="form-label">Email *</label>
            <input type="email" name="email" id="email" class="form-control" required value="<?= htmlspecialchars($_POST['email'] ?? '') ?>">
        </div>

        <div class="mb-3">
            <label for="password" class="form-label">Password *</label>
            <input type="password" name="password" id="password" class="form-control" required>
        </div>

        <div class="mb-3">
            <label for="confirm_password" class="form-label">Conferma Password *</label>
            <input type="password" name="confirm_password" id="confirm_password" class="form-control" required>
        </div>

        <button type="submit" class="btn btn-primary">Registrati</button>

        <p class="mt-3">
            Hai già un account? <a href="<?= BASE_URL ?>/Login/login.php">Accedi qui</a>
        </p>
    </form>
</main>

<?php require_once __DIR__ . '/../Components/footer.php'; ?>
