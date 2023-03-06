
<?php

session_start();

if (isset($_SESSION['login'])) {	
	// Si el usuario está registrado, mostramos su nombre y un enlace para cerrar la sesión
	echo 'Bienvenido, ' . $_SESSION['nombre'] . ' <a href="logout.php">Cerrar sesión</a>';
}
else{
	echo 'Usuario desconocido. <a href=login.php>Login</a>';
}

?>
