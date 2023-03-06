<!DOCTYPE html>
<html lang="es">
<head>
<link rel="stylesheet" type="text/css" href="estilo.css" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>Logout</title>

<?php

session_start();

// Borramos las variables de sesión
unset($_SESSION['login']);
unset($_SESSION['nombre']);
unset($_SESSION['esAdmin']);

// Destruimos la sesión
session_destroy();

// Mostramos un mensaje de despedida
echo 'Gracias por visitar nuestra web. Hasta pronto.';

?>
