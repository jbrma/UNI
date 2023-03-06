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
