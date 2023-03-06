<header>
		<h1>Mi gran página web</h1>
		<div class="saludo">
		<?php

		if (!isset($_SESSION['login'])) {
		echo 'Usuario desconocido. <a href=login.php>Login</a>';
		}
		else{
		// Si el usuario está registrado, mostramos su nombre y un enlace para cerrar la sesión
		echo 'Bienvenido, ' . $_SESSION['nombre'] . ' <a href="logout.php">Cerrar sesión</a>';

		}
		?>
		</div>
	</header>
