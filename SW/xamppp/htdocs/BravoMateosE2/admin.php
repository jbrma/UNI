<?php

session_start();

if (isset($_SESSION['esAdmin'])) {
  // Si el usuario es administrador, mostramos la consola de administración
  echo 'Controles de administración:';
} else {
  // Si el usuario no es administrador, mostramos un mensaje de acceso denegado
  echo 'Acceso denegado: no tienes permisos para administrar la web.';
}

?>
