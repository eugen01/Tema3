Student : Ionescu Eugen-Andrei
Grupa : 332CA


		Tema 3 - EGC

================================================================================

	1.Descrierea Temei

 Am pornit de la rezolvarea laboratorului 5 , urmarind implementarea folosita pt
camera.
 
 Am decis sa folosesc fisiere separate pentru cele 3 camere propuse 
(Camera_top,Camera_FPS si Camera_TPS).

 Labirintul este construit conform fisierului in.txt ; 

 La final este afisat Mesajul din message.txt folosind cuburi.
 Mesajul este generat folosind  :

	Text to ASCII generator: 

	http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something



================================================================================

	2.Rezolvarea Temei

La inceput se citeste labirintul din fisierul in.txt.
(in directorul "Exemple labirint" se gasesc cateva variante.)

fisierul are urmatorul format:
	
	- Pe prima linie:  numar_linii numar_coloane
	
	- Pe urmatoarele linii se gaseste labirintul :

	caracterul '*' = perete (cub)
	caracterul '@' = portalul
	caracterul '$' = eroul


Miscarea personajului:

	Translatiile eroului sunt similare cu cele ale unei camere FPS.
	(conform formulelor din laborator)

	Pentru acesta sunt folositi vectorii hero_forward, hero_right si hero_up.

	Eroul se poate deplasa inainte si inapoi (cu directia hero_forward) , 
	sau stanga dreapta(cu directia hero_right).

	Rotatia in jurul axei OY se face impreuna cu rotatia camerelor FPS si TPS.


Camera top-down:

	Acesta camera este statica , si "priveste" in jos spre centrul labirintului;

Camera FPS :

	Aceasta camera executa aceleasi translatii si rotatii pe care le face eroul.
	(conform formulelor din laborator)

	Astfel vectorul forward este directia inainte a eroului , vectorul right
	este la dreapta eroului si vectorul up este mereu acelasi :(0,1,0);
	
	Camera poate fi rotita in jurul axei OY.	

	In partea de jos este vizibil varful conului care indica directia.

Camera TPS : 

	Camera TPS se afla in spatele eroului , si putin deasupra.

	Translatile camerei sunt executate in functie de vectorii dreapta si inainte
	ai personajului  ,  nu de cei ai camerei.

	Directia in care priveste camera este in fata , si putin in jos.
	
	Camera se roteste in jurul axei OY o data cu eroul si camera FPS.

	Aceasta se mai poate roti si in jurul axelor OX si OZ;

	In cazul rotatiei in jurul axei OZ camera ramane centrata in spatele eroului.


================================================================================

	3.Controlul Jocului


Tastele : 

^    |
|w,  V s  - provoaca translatiile inainte si inapoi conform directiei forward


<- a si  -> d  - executa rotirea camerelor si a eroului in jurul axei OY

<- z si  -> c  - executa translatia stanga dreapta a camerelor si personajului.


^    |
|i,  V k  - determina rotatia camerei TPS in jurul axei OX

<- j si  -> l  - determina rotatia camerei TPS in jurul axei OZ


================================================================================