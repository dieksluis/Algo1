
#include <fstream>  // voor ofstream

const int MuurKans = 18;  // 18% kans op een muur
const int KratKans = 32;  // 32% kans op een krat

//*************************************************************************

// Schrijf het bord tmpbord met nrrijen rijen en nrkolommen kolommen
// naar een vast uitvoerbestand.
void schrijfbord (char tmpbord[MaxDimensie+1][MaxDimensie+1],
                  int nrrijen, int nrkolommen)
{ ofstream fuit;
  int rij, kolom;

  fuit.open ("tmpbomberman.txt", ios::out);
  if (fuit.is_open())
  { fuit << nrrijen << " " << nrkolommen << endl;
    for (rij=1;rij<=nrrijen;rij++)
    { for (kolom=1;kolom<=nrkolommen;kolom++)
        fuit << tmpbord[rij][kolom];
      fuit << endl;
    }
    fuit.close ();
  }
  else
    cout << "Bestand kon niet geopend worden." << endl;

}  // schrijfbord

//*************************************************************************

// Genereer een random Bombermanbord van dimensie rijen en dimensie
// kolommen, met de speler op een willekeurig leeg vakje.
// Elk vakje heeft MuurKans % kans om een muur te bevatten,
// en KratKans % kans om een krat te bevatten.
void genereerrandombord (int dimensie)
{ int nrrijen, nrkolommen,
      aantalleeg,   // aantal lege vakjes op het bord
      rij, kolom,
      r,            // random getal
      leegteller;   // telt lege vakjes af, tot we het lege vakje hebben,
                    // waar de speler wordt geplaatst
  char tmpbord[MaxDimensie+1][MaxDimensie+1];

  if (integerinbereik ("dimensie", dimensie, 1, MaxDimensie)
     && integerinbereik ("MuurKans", MuurKans, 0, 99)
     && integerinbereik ("KratKans", KratKans, 0, 99)
     && integerinbereik ("MuurKans + KratKans", MuurKans + KratKans, 0, 99))
    // dit is weliswaar de preconditie, maar we testen het voor de zekerheid
  { nrrijen = dimensie;
    nrkolommen = dimensie;
    do  // genereer een randombord, door voor elk vakje een random invulling
        // te bepalen.
    { aantalleeg = 0;
      for (rij=1;rij<=nrrijen;rij++)
        for (kolom=1;kolom<=nrkolommen;kolom++)
        { r = randomgetal (1, 100);
          if (r<=MuurKans)
            tmpbord[rij][kolom] = Muur;
          else
            if (r<=MuurKans+KratKans)
              tmpbord[rij][kolom] = Krat;
            else
            { tmpbord[rij][kolom] = Leeg;
              aantalleeg ++;
            }
        }
    } while (aantalleeg == 0);  // met een positieve kans op een leeg vakje
        // (want MuurKans+KratKans<100) zal het een keer voorkomen dat
        // er minstens 1 leeg vakje is

      // kies nu random een leeg vakje voor de speler
    r = randomgetal (1, aantalleeg);
    leegteller = 0;
    for (rij=1;rij<=nrrijen && leegteller<r;rij++)
      for (kolom=1;kolom<=nrkolommen && leegteller<r;kolom++)
      { if (tmpbord[rij][kolom]==Leeg)
        { leegteller ++;
          if (leegteller==r)
            tmpbord[rij][kolom] = Speler;
        }
      }

    schrijfbord (tmpbord, nrrijen, nrkolommen);

  }  // bruikbare waardes

}  // genereerrandombord
