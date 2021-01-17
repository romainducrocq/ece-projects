<!DOCTYPE html>
<html>
    <head>
        <!-- En-tête de la page -->
        <meta charset="utf-8" />
        <title>Inscription</title>

        <!-- CSS -->
    
        <link rel="stylesheet"  href="style.css">
    </head>

    <body>

<div>
<div class ="purple2 ">
<h1>R2D'BOOK</h1>
<h1>Inscription</h1>
</div>

<?php
include('bdd.php');
    
    if(isset($_POST['submit']))
    {
        $nom = $_POST['nom'];
        $prenom = $_POST['prenom'];
        $pseudo = $_POST['pseudo'];
        $passe = $_POST['passe'];
        $passe2 = $_POST['passe2'];
        $email = $_POST['email'];

        if(empty($nom))
            $errors[]="Veuillez saisir un nom";
        if(empty($prenom))
            $errors[]="Veuillez saisir un prenom";
        if(empty($pseudo))
            $errors[]="Veuillez saisir un pseudo";
        elseif(isTakenPseudo_BDD($pseudo))
            $errors[]="Ce pseudo est déjà pris";
        if(empty($passe))
            $errors[]="Veuillez saisir un un mot de passe";
        elseif(empty($passe2))
            $errors[]="Veuillez saisir à nouveau le mot de passe";
        elseif($passe!=$passe2)
            $errors[]="Les mots de passes ne correspondent pas";
        elseif(isTakenPasse_BDD($passe))
            $errors[]="Ce mot de passe est déjà pris";
        if(empty($email))
            $errors[]="Veuillez saisir un email";
        elseif(!preg_match("#^[a-z0-9._-]+@[a-z0-9._-]{2,}\.[a-z]{2,4}$#",$email))
            $errors[]="Veuillez saisir un email valide";
        elseif(isTakenEmail_BDD($email))
            $errors[]="Cet email est déjà pris";

        if(!empty($errors))
        {
            foreach($errors as $error)
            {
                echo "<div class = 'error'>".$error."</div>";
            }
        }
        else 
        {
            inscription_BDD($nom,$prenom,$pseudo,$passe,$email);
            exit('<a href="index.php"> Vous êtes inscrit, connectez vous ! </a>');
        }
    }

?>

<!-- action="inscription.php" -->
 <form  class="contenu2" method="post">
 <div>
 <label>Nom: <input type="text" name="nom"/></label>
 </div><br>

 <div>
           <label>Prenom: <input type="text" name="prenom"/></label>
 </div>
 <br/>
 <div>
           <label>Pseudo: <input type="text" name="pseudo"/></label>
 </div>
 <br/>

 <div>
            <label>Mot de passe: <input type="password" name="passe"/></label>
</div>
<br/>

<div>
            <label>Confirmation du mot de passe: <input type="password" name="passe2"/></label>
</div>
<br/>

<div>
             <label>Adresse e-mail: <input type="text" name="email"/></label>
<div>
<br/>

<div>
<input type="submit" value="M'inscrire" name="submit"/>
</div>
<br>

</form>



    </body>
</html>