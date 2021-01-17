<?php
if (isset($_POST['upload'])) 
echo "ok";
{ 


echo "ok";
$file = $_FILES['fichier']['tmp_name']; 
$chemin='compo/';
$file_tmp =$file['tmp_name']; 
$nomfichier = basename($_FILES['fichier']['name']);
$chemin_destination = 'compo/';  
move_uploaded_file($file_tmp, $dossier . $nomfichier)

}
?>