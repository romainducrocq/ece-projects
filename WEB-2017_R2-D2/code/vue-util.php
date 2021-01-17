
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
<option value="">Ma page</option>
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

?>
 
<div class="menu1"> <!--  onglets -->
   <a class="onglet" href="propos.php">A propos</a> 
  <a class="onglet" href="ami.html">Amis</a> 
  <span class="onglet-actif">Publications</span> 
  <a class="onglet" href="photo.php">Photos</a> 
  <a class="onglet" href="video.html">Video</a> 
  <a class="onglet" href="event.html">Evenement</a> 
  <a class="onglet" href="chrono.html">Chronologie</a> 

</div>

</br>

<div style="padding:80px; border:2px dashed purple;">
<p class="publier"> Publier ici au grès de vos envies <p>
<FORM>
<TEXTAREA name="publication " rows=10 cols=100> </TEXTAREA>
</FORM>
<input type="submit" value="Publier"   />
</div>


</body>
</html>