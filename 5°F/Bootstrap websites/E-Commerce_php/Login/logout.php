<?php
session_start();
session_unset();
session_destroy();
require_once __DIR__ . '/../config.php';
header('Location: ' . BASE_URL . '/' . 'Login/login.php');
exit;