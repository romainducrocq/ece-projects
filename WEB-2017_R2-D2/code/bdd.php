<!--connexion à la base de données (d'après https://www.w3schools.com/PHP/php_ref_mysqli.asp)-->

<?php //toutes les fonctions qui vont utiliser la bdd, le query et le sql
	session_start();

	define('DB_USER', 'root');
	define('DB_PASS', 'root');
	define('DB_SERVER', '127.0.0.1');
	define('DB_DATABASE','r2d2');
	$con = mysqli_connect(DB_SERVER, DB_USER, DB_PASS); //connexion au serveur localhost
  $_SESSION['con'] = $con;


	if(mysqli_select_db($con,DB_DATABASE)) //connexion à la bdd
		mysqli_set_charset($con,"utf8"); //definition du style par defaut

	elseif (mysqli_connect_errno()) //gestion des erreurs
  		echo "Failed to connect to MySQL: " . mysqli_connect_error();


  	//FAIRE UNE REQUETE SQL : Query -> mysqli_query(BDD, "REQUETE SQL")

  	function inscription_BDD($nom,$prenom,$pseudo,$passe,$email) //creer un nouvel utilisateur
  	{

  		mysqli_query($_SESSION['con'], "INSERT INTO utilisateur(idUtilisateur,Nom,Prenom,Pseudo,Mdp,Email) 
  			VALUES('','$nom','$prenom','$pseudo','$passe','$email')");

  	}

    function inscription_BDD_photo($lieu_photo,$date_photo,$proprietaire,$description_photo,$restriction) //ajoute une nouvelle photo
  	{

mysqli_query($_SESSION['con'], "INSERT INTO photo(id_photo,lieu_photo,date_photo,nom_photo,proprietaire,description_photo,rest) 
  			VALUES('','$lieu_photo','$date_photo','','$proprietaire','$description_photo','$restriction')");
     
              
  	}


  	function isTakenPseudo_BDD($pseudo) //est ce que le pseudo est dispo
  	{
		$result = mysqli_query($_SESSION['con'], "SELECT idUtilisateur FROM utilisateur WHERE Pseudo='$pseudo'");
		if(mysqli_num_rows($result) > 0) 
			return TRUE;
		else 
			return FALSE;

  	}

  	function isTakenPasse_BDD($passe) //est ce que le mdp est dispo
  	{
  		$result = mysqli_query($_SESSION['con'], "SELECT idUtilisateur FROM utilisateur WHERE Mdp='$passe'");
  		if(mysqli_num_rows($result) > 0)
			return TRUE;
		else 
			return FALSE;
  	}

  	function isTakenEmail_BDD($email) //est ce que l'email est dispo
  	{
  		$result = mysqli_query($_SESSION['con'], "SELECT idUtilisateur FROM utilisateur WHERE Email='$email'");
  		if(mysqli_num_rows($result) > 0)
			return TRUE;
		else 
			return FALSE;
  	}

  	function getPasswordWithEmail_BDD($email) //combinaison mdp + email ok
  	{
  		$result = mysqli_query($_SESSION['con'], "SELECT Mdp FROM utilisateur WHERE Email='$email'");
  		return mysqli_fetch_row($result)[0];
  	}

    function getPseudo_BDD($email) // on récupère le pseudo
    {
      $result = mysqli_query($_SESSION['con'], "SELECT Pseudo FROM utilisateur WHERE Email='$email'");
      return mysqli_fetch_row($result)[0];
    }

//marche pas encore

  	function getAllInfos_BDD($pseudo) //recuperer toutes les infos du membre connecté
  	{
  		$infos = array();
  		//$pseudo = $_SESSION['pseudo'];
  		$result = mysqli_query($_SESSION['con'],"SELECT * FROM utilisateur WHERE Pseudo='$pseudo'");
  		while ($row=mysqli_fetch_assoc($result))
    		$infos[]=$row;
    	return $infos;
  	}



?>









