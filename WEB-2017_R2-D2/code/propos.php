

<!DOCTYPE html>

<html>
<head>
<meta http-equiv="Content-Type" content="text/html" charset="iso-8859-1" />
 <meta charset="utf-8" />
<link rel="stylesheet"  href="style-vue.css">

</head>

<script>

function selection() {
  i = document.Choix.Liste.selectedIndex;
  if (i == 0) return;
  url = document.Choix.Liste.options[i].value;
  parent.location.href = url;
}

</script>

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

<?php
  include('bdd.php');
  $infos = getAllInfos_BDD($_SESSION['pseudo']);

  foreach($infos as $info)
    echo " Bienvenue ".$info['Pseudo'];
   

?>


<div class="menu1"> <!--  onglets -->
  <span class="onglet-actif" href="propos.php">A propos</span> 
  <a class="onglet" href="ami.html">Amis</a> 
  <a class="onglet" href="vue-util.php">Publications</a> 
  <a class="onglet" href="photo.php">Photos</a> 
  <a class="onglet" href="video.html">Video</a> 
  <a class="onglet" href="event.html">Evenement</a> 
  <a class="onglet" href="chrono.html">Chronologie</a> 

</div>

</br>

<div style="padding:100px; border:2px dashed green;">
<?php
  
 
?>


<FORM>
<TEXTAREA name="publication " rows=10 cols=100> </TEXTAREA>
</FORM>
<input type="submit" value="Modifier description"  />
</div>


</body>
</html>