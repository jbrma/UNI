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

    header("Location: admin.php");
        exit();
  }

    else{
        header("Location: login.php");
        exit();
    }
?>

<?php
header("Location: index.php");
echo 'Usuario o contraseña incorrectos.';
?>
