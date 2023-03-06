<?php
session_start();

// Obtenemos los datos del formulario
$username = $_POST['usuario'];
$password = $_POST['password'];

  // Comprobamos si el usuario es válido)) {
    
  if($username == "user" && $password == "userpass") {
    // Añadimos las variables a la sesión
    $_SESSION['login'] = true;
    $_SESSION['nombre'] = "Usuario";
    
  }
 
  else if ($username == "admin" && $password == "adminpass"){

    // Añadimos las variables a la sesión
    $_SESSION['login'] = true;
    $_SESSION['nombre'] = "Administrador";
    $_SESSION['esAdmin'] = true;

    //header("Location: admin.php");
    //    exit();
  }

?>


<!DOCTYPE html>
<html lang="es">
<head>
<link rel="stylesheet" type="text/css" href="estilo.css" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>Procesar login</title>
</head>
<body>
    <div id="contenedor">

        <?php
            require("cabecera.php");
            require("sidebarIzq.php");
        ?>

        <main>
        <article>
            <?php
                if (!isset($_SESSION["login"])) { //Usuario no es valido
                    echo "<h1>[ERROR]: Inicio de Sesión</h1>";
                    echo "<p>El nombre de usuario o contraseña no son válidos.</p>";
                }
                else { //Usuario registrado
                    echo "<h1>Bienvenido {$_SESSION['nombre']}</h1>";
                    echo "<p>Usa el menú de la izquierda para navegar.</p>";
                }
            ?>
            </article>
        </main>

        <?php
            include("sidebarDer.php");
            include("pie.php");
        ?>

    </div> <!-- Fin del contenedor -->
    
</body></html>

<?php
header("Location: index.php");
?>
