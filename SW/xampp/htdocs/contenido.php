<!DOCTYPE html>
<html lang="es">
<head>
<link rel="stylesheet" type="text/css" href="estilo.css" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>Contenido</title>

<?php
session_start();

if(isset($_SESSION['login'])) {
  // Si el usuario está logueado, se muestra el contenido exclusivo
  echo "<h1>Bienvenido al contenido exclusivo</h1>";
  echo "<p>Aquí podrás encontrar información de alta calidad que no está disponible para usuarios no registrados.</p>";
} else {
  // Si el usuario no está logueado, se muestra un mensaje de invitación a iniciar sesión
  echo "<h1>Contenido exclusivo para usuarios registrados</h1>";
  echo "<p>Lo sentimos, pero este contenido sólo está disponible para usuarios registrados. Por favor, inicie sesión o regístrese para acceder al contenido.</p>";
}
?>
