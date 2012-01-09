<?php

	include('utils.php');
?>

<html>
	<head>
		<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="fr" lang="fr">
		<meta name="title"              content="Projet C2a"/>
		<meta http-equiv="imagetoolbar" content="no" />
		<meta name="description"        content=""/>
		<meta name="keywords"           content=""/>
		<meta name="language"           content="fr"/>    
		<meta http-equiv="content-type" content="text/html;charset=utf-8" />

		<link rel="stylesheet" type="text/css" href="./style.css"/>
		
		<script language='JavaScript'> setTimeout('window.location.reload()',5000); </script>
	</head>
	<body>

	<?php
	
		$result = "<h1>Projet C2A</h1>";
		$result .= "<br/>";

		
		$connect = connectBdd("ayaida@sql.free.fr","ayaida","cresticc2a", "ayaida");

		$query_1 = "SHOW TABLES;";
		$req_1 = mysql_query ($query_1);
		while ($data_1 = mysql_fetch_assoc($req_1))
		{ 
			$table = $data_1["Tables_in_ayaida"];

			$result .= "<h2>".$table."</h2>";
			$result .="<table  border='1'>";

			$query_2 = "SELECT * FROM $table";
			$req_2 = mysql_query ($query_2);
			while ($data_2 = mysql_fetch_assoc($req_2))
			{
				$result .="<tr>";
				$result .="<td>".$data_2["type"] ."</td>";
				$result .="<td>".$data_2["value"] ."</td>";
				$result .="<td>".$data_2["unit"] ."</td>";
				$result .="<td>".$data_2["description"] ."</td>";
				$result .="</tr>";
			}

			$result .="</table>";
			$result .="<br/>";
		}
           
		mysql_close($connect);				

		echo $result;
	?>
	
	</body>
</html>
