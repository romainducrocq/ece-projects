<?php
$img=$_FILES['fichier'];
    
    if(is_dir('reper/'))
        echo"ok";

if(!empty($_FILES))
{
    print_r($_FILES);
    
    move_uploaded_file($img['tmp_name'],"reper/".$img['name']); /// on déplace la photo dans le dossier reper de htdocs
    
}

?>

<!DOCTYPE html>

<html>
<head>

 <meta charset="utf-8" />
<link rel="stylesheet"  href="style-photo.css">


<script>

function selection() {   /// script pour affecter une action a chaque bouton du menu déroulant
  i = document.Choix.Liste.selectedIndex;
  if (i == 0) return;
  url = document.Choix.Liste.options[i].value;
  parent.location.href = url;
}

</script>

</head>


<body>
<div class ="purple ">


<FORM NAME="Choix">   <!-- menu déroulant  -->
<select class="droite" NAME="Liste" onchange="selection()">
<option value="">Ma page </option>
<option value="">Messages</option>
<option value="index.php">Déconnexion</option>
</select>
</FORM>



<form class="contenu" action="/ma-page-de-traitement" method="post">

    <div>
        <label>Recherche:</label>
        <input type="text" name="recherche" />
    </div>
    </br>
    
    <div>
    <input type="submit" value="Rechercher maintenant" />
    </div>
</form>
</div>



<div class="menu1"> <!-- onglets -->
   <a class="onglet" href="propos.php">A propos</a> 
  <a class="onglet" href="ami.html">Amis</a> 
  <a class="onglet" href="vue-util.php" >Publications</a> 
  <span class="onglet-actif" href="photo.php">Photos</span> 
  <a class="onglet" href="video.html">Video</a> 
  <a class="onglet" href="event.html">Evenement</a> 
  <a class="onglet" href="chrono.html">Chronologie</a> 

</div>
                <div class="ajout1">
                <label for="email">Selectionnez votre photo:</label>
               <form method="post" action="photo_ajout.php" enctype="multipart/form-data">
               <input type="file" name="fichier" /> 
              <input type="submit" name="upload" value="Ajouter" /> </form>
              </div>


<form class="ajout1" method="post">

            
                <div>
                      <label>Lieu: <input type="text" name="lieu_photo"/></label>
              </div>
               <br/>
                <div>
                      <label>Date: <input type="date" name="date_photo"/></label>
              </div>
               <br/>
               <div>
                      <label>Description: <input type="text" name="description_photo"/></label>
              </div>
               <br/>
               <div>
                      <label>Restriction (publique ou privée): <input type="text" name="restriction"/></label>
              </div>
               <br/>
                      <input type="submit" value="Envoyer" name="submit"   />
      </div>
    
</form>

<form  action="photo.php">
     <div class="button3">
    <input type="submit" value="Retour" name="retour"   />
    </div>
     </form>

     <?php
include('bdd.php');
    if(isset($_POST['submit']))   /// on ajoute une photo à la bdd
    {   

        $lieu_photo = $_POST['lieu_photo'];
        $date_photo = $_POST['date_photo'];
        $description_photo = $_POST['description_photo'];
        $restriction = $_POST['restriction'];
        

        if(empty($lieu_photo))
            $errors[]="Veuillez saisir un lieu";
        if(empty($date_photo))
            $errors[]="Veuillez saisir une date";
        if(empty($description_photo))
            $errors[]="Veuillez saisir une description";
         if(empty($restriction))
            $errors[]="Veuillez rendre la photo publique ou privée";
        if(!empty($errors))
        {
            foreach($errors as $error)
            {
                echo "<div class = 'error'>".$error."</div>";
            }
        }
        else 
        {   
            $proprietaire='RD';
            $infos = getAllInfos_BDD($_SESSION['pseudo']);
            foreach($infos as $info)
           $proprietaire=$info['Pseudo'];
            
            inscription_BDD_photo($lieu_photo,$date_photo,$proprietaire,$description_photo,$restriction); /// on appelle la fonction d'inscription
            echo"La photo a bien été ajoutée";
        }
    }
    

             
  

  
?>

</body>
</html>