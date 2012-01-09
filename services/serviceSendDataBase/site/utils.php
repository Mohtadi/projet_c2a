<?php
	function connectBdd ($_host , $_user , $_pass , $_bdd)
	{
		$result = mysql_connect ($_host , $_user , $_pass) or die ('Impossible de se connecter');
		mysql_select_db ("$_bdd") or die ('Impossible de séléctionner la base de donnée');
		mysql_query('SET NAMES utf8');
		return $result;
	}

	function dropTable($_table)
	{
		$query = "DROP TABLE $_table;";
		$req = mysql_query ($query);
		return $req;
	}

	function createTable($_tables)
	{
		$query = "SHOW TABLES;";
		$req = mysql_query ($query);
		while ($data = mysql_fetch_assoc($req))
		{ 
			$table = $data["Tables_in_ayaida"];
			$query = "DROP TABLE $table;";
			$req2 = mysql_query ($query);
		}

		for ($i = 0 ; $i < count($_tables) ; $i++)
		{
			$table = $_tables[$i][0];
			$query = "CREATE TABLE $table (
				type 	    VARCHAR(256) NOT NULL  PRIMARY KEY ,
				value       VARCHAR(256) NOT NULL default '',
				unit        VARCHAR(256) NOT NULL default '',
				description VARCHAR(256) NOT NULL default '');";
			$req = mysql_query ($query);
		}
		return $req;
	}

	function insert($_table , $_type , $_value , $_unit , $_description)
	{	
		//Si le type n'est pas dans la base de données je l'insert sinon je l'update
		$query = "SELECT * FROM $_table WHERE type = '$_type'";
		$req = mysql_query ($query);

		$exist_type = false;
		while ($data = mysql_fetch_assoc($req))
		{ 
			$type = $data["type"];
			if ($type == $_type)
			{
				$exist_type = true;
			}
		}

		if ($exist_type == false)
		{
			$query = "INSERT INTO $_table (type,value,unit,description) VALUES ('$_type' , '$_value' , '$_unit' , '$_description')";
			$req = mysql_query ($query);

		}
		else
		{
			update($_table , $_type , $_value , $_unit , $_description);
		}
		return $req;
	}

	function update($_table , $_type , $_value , $_unit , $_description)
	{	
		$query = "UPDATE $_table SET value = '$_value' , unit = '$_unit' , description = '$_description' WHERE type = '$_type'";
		$req = mysql_query ($query);
		return $req;
	}

	$connect = "";

	if (isset ($_POST['action']))
        {
		switch ($_POST['action'])
		{
			case "CREATE_TABLE" :	
				$connect = connectBdd("ayaida@sql.free.fr","ayaida","cresticc2a", "ayaida");
				if (isset ($_POST['table']))
				{
					$tables = $_POST['table'];
					$tab_tables 		= preg_split("/[-]+/", $tables, -1, PREG_SPLIT_OFFSET_CAPTURE);
					createTable($tab_tables);	
				}				
				mysql_close($connect);				
			break;

			case "INSERT" :
				$table 		= "";
				$type 		= "";
				$value 		= "";
				$unit 		= "";
				$description 	= "";

				if (isset ($_POST['table']))
				{
					$table = $_POST['table'];	
				}		

				if (isset ($_POST['type']))
				{
					$type = $_POST['type'];
				}

				if (isset ($_POST['value']))
				{
					$value = $_POST['value'];
				}

				if (isset ($_POST['unit']))
				{
					$unit = $_POST['unit'];
				}

				if (isset ($_POST['description']))
				{
					$description = $_POST['description'];
				}	

				$tab_type 		= preg_split("/[-]+/", $type, -1, PREG_SPLIT_OFFSET_CAPTURE);
				$tab_value 		= preg_split("/[-]+/", $value, -1, PREG_SPLIT_OFFSET_CAPTURE);
				$tab_unit		= preg_split("/[-]+/", $unit, -1, PREG_SPLIT_OFFSET_CAPTURE);
				$tab_description 	= preg_split("/[-]+/", $description, -1, PREG_SPLIT_OFFSET_CAPTURE);

				$connect = connectBdd("ayaida@sql.free.fr","ayaida","cresticc2a", "ayaida");

				for ($i=0 ; $i < count($tab_type) ; $i++)
				{
					insert ($table , $tab_type[$i][0] , $tab_value[$i][0] , $tab_unit[$i][0] , $tab_description[$i][0]);
				}

				mysql_close($connect);	
			break;

			default :
			break;
		}

	}	
?>

