<?php
if(!empty($_FILES))
{
    
    print_r($_FILES);
    $img=$_Files['img'];
    move_uploaded_file($img['tmp_name'], "image/".$img['name']);
}
?>


<!DOCTYPE html>

<HTML>
 <HEAD>
  <TITLE>Titre de la page</TITLE>
   <meta charset="utf-8" />
 </HEAD>

 <BODY>
 
<form method="post" action="test.php" enctype="multipart/form-data">
<input type="file" name="img" />
<input type="submit" name="envoyer" />

    </BODY>
</HTML>