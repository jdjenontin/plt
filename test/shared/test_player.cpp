#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Player.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestCalculation)
{
    
    Player player1 = Player();
    Player player2 = Player(2);
    std::vector<Country*> listCountry;
    std::vector<Card*> listCard;
    Country pays0 = Country("Alaska", 0);
    Country pays1 = Country("Territoires du Nord-Ouest", 1);
    Country pays2 = Country("Alberta", 2);
    Card carteTest = Card();
    Card carte0 = Card("Alaska", Infantry);
    Card carte1 = Card("Territoires du Nord-Ouest", Cavalry);
    Card carte2 = Card("Alberta", Artillery);
    listCountry.push_back(&pays0);
    listCountry.push_back(&pays1);
    listCountry.push_back(&pays2);
    listCard.push_back(&carte0);
    listCard.push_back(&carte1);
    listCard.push_back(&carte2);

    // Tests getters setters
    {
        player1.addCard(&carte0);
        player1.addCard(&carte1);
        player1.addCard(&carte2);
        player1.addCountry(&pays0);
        player1.addCountry(&pays1);
        player1.addCountry(&pays2);
        BOOST_CHECK_EQUAL(player1.getTypeplayer(), HUMAN);
        BOOST_CHECK_EQUAL(player2.getOrder(), 2);
        player1.setName("Paul");
        player1.setStatus(LOSE);
        BOOST_CHECK_EQUAL(player1.getName(), "Paul");
        BOOST_CHECK_EQUAL(player2.getStatus(), PLAYING);
        BOOST_CHECK_EQUAL(player1.getStatus(), LOSE);
        for (int i = 0; i<3; i++){
            BOOST_CHECK_EQUAL(player1.getListCard().at(i)->getNameCountry(),listCard.at(i)->getNameCountry());
            BOOST_CHECK_EQUAL(player1.getListCountry().at(i)->getNameCountry(),listCountry.at(i)->getNameCountry());
        }
        BOOST_CHECK_EQUAL(player1.existCountry(pays2), true);
        player1.deleteCard(&carte2);
        player1.deleteCountry(&pays2);
        for (int i = 0; i<2; i++){
            BOOST_CHECK_EQUAL(player1.getListCard().at(i)->getNameCountry(),listCard.at(i)->getNameCountry());
            BOOST_CHECK_EQUAL(player1.getListCountry().at(i)->getNameCountry(),listCountry.at(i)->getNameCountry());
        }
        BOOST_CHECK_EQUAL(player1.existCountry(pays2), false);
        sf::Color couleur;
        couleur.r = 255;
        couleur.g = 127;
        couleur.b = 0;
        player1.setColor(couleur);
        BOOST_CHECK_EQUAL(player1.getColor().r, 255);
        BOOST_CHECK_EQUAL(player1.getColor().g, 127);
        BOOST_CHECK_EQUAL(player1.getColor().b, 0);

        std::string countryList[42] = {"Alaska", "Territoire du Nord-Ouest", "Alberta", "Ontario", "Groenland", "Quebec", "Ouest des Etat-Unis", "Est des Etats-Unis", "Amerique Centrale", "Venezuela", "Perou", "Bresil", "Argentine", "Afrique du Nord", "Egypte", "Afrique de l'Est", "Congo", "Afrique du Sud", "Madagascar", "Islande", "Grande-Bretagne", "Scandinavie", "Europe du Nord", "Ukraine", "Europe de l'Ouest", "Europe du Sud", "Moyen-Orient", "Afghanistan", "Ural", "Siberie", "Yakutsk", "Irkoutsk", "Mongolie", "Kamchatka", "Japon", "Chine", "Inde", "Siam", "Indonesie", "Nouvelle-Guinee", "Australie Orientale", "Australie Occidentale"};
        std::vector<Country> listeDePays;
        for (int i = 0; i < 42; i++) listeDePays.push_back(Country(countryList[i],i));
        for (int i = 0; i < 42; i++) player2.addCountry(&(listeDePays.at(i)));
        BOOST_CHECK_EQUAL(player2.continentBonusTroop(), 38);
    }
}