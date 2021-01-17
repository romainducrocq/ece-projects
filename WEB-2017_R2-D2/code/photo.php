<!DOCTYPE html>

<html>
<head>

 <meta charset="utf-8" />
<link rel="stylesheet"  href="style-photo.css">
<script>

function selection() {
  i = document.Choix.Liste.selectedIndex;
  if (i == 0) return;
  url = document.Choix.Liste.options[i].value;
  parent.location.href = url;
}

</script>

</head>


<body>
<div class ="purple ">


<FORM NAME="Choix">
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



<div class="menu1"> <!-- début de la boite contenant les onglets -->
   <a class="onglet" href="propos.php">A propos</a> <!-- onglet inactif -->
  <a class="onglet" href="ami.html">Amis</a> <!-- onglet inactif -->
  <a class="onglet" href="vue-util.php" >Publications</a> <!-- onglet ACTIF -->
  <span class="onglet-actif" href="photo.php">Photos</span> <!-- onglet inactif -->
  <a class="onglet" href="video.html">Video</a> <!-- onglet inactif -->
  <a class="onglet" href="event.html">Evenement</a> <!-- onglet inactif -->
  <a class="onglet" href="chrono.html">Chronologie</a> <!-- onglet inactif -->

</div>

<!--  <figure>
<img  src="karim1.jpg" alt="karim1" />
</br> <figcaption> Avril 2016 </figcaption>
</figure>-->


<?php
  /// code php pour afficher les photos entrées par l'utilisateur
  $dos="reper/";
  $dir= opendir($dos);
  while($file=readdir($dir))
  {

    ?>
    <img src="reper/<?php echo $file; ?>"/>   
    <?php
  }
?>




</br>
     
     <form  action="photo_ajout.php">
     <div class="button1">
    <input type="submit" value="Ajouter photo" name="ajouter_photo"   />
    </div>
    

    <div class="button2">
    <input type="button" value="Creer Album photo "  />
    </div>

    <div class="button2">
    <input type="button" value="Retirer photo "  />
    </div>
    </form>




</body>
</html>