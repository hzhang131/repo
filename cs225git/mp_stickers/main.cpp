#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  /*
  Image map; map.readFromFile("tests/Midwest.png");
  Image I; I.readFromFile("tests/i.png");
  Image P; P.readFromFile("tests/p.png");
  Image W; W.readFromFile("tests/w.png");
  Image IU; IU.readFromFile("tests/iu.png");
  Image OSU; OSU.readFromFile("tests/osu.png");
  Image M; M.readFromFile("tests/m.png");
  Image MN; MN.readFromFile("tests/mn.png");
  Image IS; IS.readFromFile("tests/is.png");
  Image N; N.readFromFile("tests/n.png");
  Image NU; NU.readFromFile("tests/NW1.png");
  //Image UC; UC.readFromFile("tests/uc.png");
  Image ISU; ISU.readFromFile("tests/ISU.png");
  Image MSU; MSU.readFromFile("tests/msu.png");
  Image WUSTL; WUSTL.readFromFile("tests/wustl.png");
  map.illinify();
  map.scale(10);
  I.scale(0.8);
  P.scale(0.55);
  W.scale(0.2);
  IU.scale(0.45);
  OSU.scale(0.2);
  M.scale(0.2);
  MN.scale(0.2);
  IS.scale(0.2);
  N.scale(0.15);
  NU.scale(0.08);
  //UC.scale(0.3);
  MSU.scale(0.15);
  WUSTL.scale(0.7);
  ISU.scale(0.6);
  StickerSheet s1(map, 30);
  s1.addSticker(I, 1110*5, 840*5);
  s1.addSticker(P, 1170*5, 795*5);
  s1.addSticker(W, 1030*5, 580*5);
  s1.addSticker(IU, 1200*5, 920*5);
  s1.addSticker(OSU, 1440*5, 780*5);
  s1.addSticker(M, 1380*5, 630*5);
  s1.addSticker(MN, 740*5, 390*5);
  s1.addSticker(IS, 720*5, 690*5);
  s1.addSticker(N, 560*5, 850*5);
  s1.addSticker(NU, 1110*5, 650*5);
  //s1.addSticker(UC, 1100*5, 680*5);
  s1.addSticker(MSU, 1330*5, 580*5);
  s1.addSticker(WUSTL, 940*5, 990*5);
  s1.addSticker(ISU, 1050*5, 800*5);
  */
  Image europe; europe.readFromFile("tests/EU.png");
  europe.scale(920,920);
  europe.writeToFile("myImage.png");
}
