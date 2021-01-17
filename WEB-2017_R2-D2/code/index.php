

<!DOCTYPE html>
<html>
    <head>
        <!-- En-tête de la page -->
        <meta charset="utf-8" />
        <title>Ma page HTML</title>

        <!-- CSS -->
    
        <link rel="stylesheet"  href="style.css">
    </head>

    <body>
 <div class ="purple ">
 <h1>R2D'BOOK</h1>
 <h1>Bienvenue sur R2-D'BOOK</h1>
 </div>

<p>
    
    <img class ="position" src="R.jpg" alt="R2-D2" />
</p>

<?php
    include('bdd.php');

    if(isset($_POST['submit']))
    {
        $email = $_POST['email'];
        $passe = $_POST['passe'];

        if(empty($email))
            $errors[]="Veuillez saisir votre email";
        elseif(!preg_match("#^[a-z0-9._-]+@[a-z0-9._-]{2,}\.[a-z]{2,4}$#",$email))
            $errors[]="Veuillez saisir un email valide";
        if(empty($passe))
            $errors[]="Veuillez saisir votre mot de passe";
        if(empty($errors))
        {
            if(isTakenEmail_BDD($email))
            {
            if($passe!=getPasswordWithEmail_BDD($email))
                $errors[]="Mot de passe invalide";
            }
            else 
            $errors[]="Email invalide";
        }
        

        if(!empty($errors))
        {
            foreach($errors as $error)
            {
                echo "<div class = 'error'>".$error."</div>";
            }
        }
        else 
        {
            
            $_SESSION['pseudo'] = getPseudo_BDD($email);
            echo"<a href=\"propos.php\"> Identification réussie, connectez vous ! </a>";
        }

    }

?>


<form class="contenu" method="post">

    <div>
        <label for="email">Email:</label>
        <input type="text" name="email" id="email" />
    </div>
    </br>
    <div>
        <label for="passe">Votre mot de passe :</label>
       <input type="password" name="passe" id="passe" />
    </div>
     </br>
    <div>
    <input type="submit" value="Envoyer" name="submit" />
    </div>
    <p>Vous n'avez pas encore de compte ?</p>
    <p> <a href="inscription.php">Inscrivez-vous ici</a> </p>
</form>



    </body>
</html>