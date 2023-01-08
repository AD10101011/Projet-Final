.SILENT:

CO=g++ -D DEBUG2
OBJS_QT = main.o applicgaragewindow.o moc_applicgaragewindow.o
OBJS = classe/Exception.o classe/OptionException.o classe/Option.o classe/Voiture.o  classe/Personne.o classe/Intervenant.o classe/Employe.o classe/modele.o classe/PasswordException.o classe/Iterateur.o classe/Vecteur.o classe/Client.o classe/VecteurTrie.o classe/Garage.o classe/Contrat.o

PROGRAMS = ApplicGarage

all:	$(PROGRAMS)

ApplicGarage:	$(OBJS_QT) $(OBJS)
		echo Creation de ApplicGarage...
		$(CO) -Wl,-O1 -o ApplicGarage $(OBJS_QT) $(OBJS) /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread 					
		#rm main.o

main.o:	main.cpp
		echo Creation de main.o
		$(CO) -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o main.o main.cpp

applicgaragewindow.o:	applicgaragewindow.cpp applicgaragewindow.h ui_applicgaragewindow.h
		echo Creation de applicgaragewindow.o
		$(CO) -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o applicgaragewindow.o applicgaragewindow.cpp

moc_applicgaragewindow.o:	moc_applicgaragewindow.cpp applicgaragewindow.h
		echo Creation de moc_applicgaragewindow.o
		$(CO) -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o moc_applicgaragewindow.o moc_applicgaragewindow.cpp


classe/Garage.o:			classe/Garage.cpp classe/Garage.h
							echo "Création de Garage.o"
							g++ classe/Garage.cpp -c -o classe/Garage.o

classe/Contrat.o:			classe/Contrat.cpp classe/Contrat.h
							echo "Création de Contrat.o"
							g++ classe/Contrat.cpp -c -o classe/Contrat.o

classe/VecteurTrie.o:		classe/VecteurTrie.cpp classe/VecteurTrie.h
							echo "Creation de VecteurTrie.o"
							g++ classe/VecteurTrie.cpp -c -o classe/VecteurTrie.o

classe/Vecteur.o:			classe/Vecteur.h classe/Vecteur.cpp
							echo "Création d'Vecteur.o"
							g++ classe/Vecteur.cpp -c -o classe/Vecteur.o

classe/Client.o:			classe/Client.h classe/Client.cpp
							echo "Création de Client.o"
							g++ classe/Client.cpp -c -o classe/Client.o


classe/Iterateur.o:			classe/Iterateur.h classe/Iterateur.cpp
							echo "Création d'Iterateur.o"
							g++ classe/Iterateur.cpp -c -o classe/Iterateur.o

classe/Exception.o:			classe/Exception.h classe/Exception.cpp
							echo "Création de Exception.o"
							g++ classe/Exception.cpp -c -o classe/Exception.o

classe/OptionException.o: 	classe/OptionException.h classe/OptionException.cpp
							echo "Création de OptionException.o "
							g++ classe/OptionException.cpp -c -o classe/OptionException.o

classe/Option.o:			classe/Option.h classe/Option.cpp
							echo "Création de option.o"
							g++ classe/Option.cpp -c -o classe/Option.o

classe/Voiture.o:			classe/Voiture.h classe/Voiture.cpp
							echo "Création de voiture.o"
							g++ classe/Voiture.cpp -c -o classe/Voiture.o

classe/Employe.o:			classe/Employe.h classe/Employe.cpp
							echo "Création de Employe.o"
							g++ classe/Employe.cpp -c -o classe/Employe.o

classe/Intervenant.o:		classe/Intervenant.h classe/Intervenant.cpp
							echo "Création de Intervenant.o"
							g++ classe/Intervenant.cpp -c -o classe/Intervenant.o

classe/Personne.o:			classe/Personne.h classe/Personne.cpp
							echo "Création de Personne.o"
							g++ classe/Personne.cpp -c -o classe/Personne.o

classe/modele.o:			classe/Modele.h classe/Modele.cpp
							g++ classe/Modele.cpp -c -o classe/modele.o
							echo "Création de modele.o"

classe/PasswordException.o: classe/PasswordException.h classe/PasswordException.cpp
							g++ classe/PasswordException.cpp -c -o classe/PasswordException.o
							echo "Création de PasswordException.o"



clean:
	@rm -f $(OBJS_QT) core
	rm classe/*.o

clobber:	clean
	@rm -f tags $(PROGRAMS) *~ *.log
