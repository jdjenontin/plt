#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Player.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestCalculation)
{
    
    std::shared_ptr<Player> player1(new Player());
    std::shared_ptr<Player> player2(new Player(2));
    std::vector<std::shared_ptr<Country> > listCountry;
    std::vector<std::shared_ptr<Card> > listCard;
    std::shared_ptr<Country> ala(new Country("Alaska", 0));
    std::shared_ptr<Country> terr(new Country("Territoires du Nord-Ouest", 1));
    std::shared_ptr<Country> alb(new Country("Alberta", 2));
    Country Alberta(Country("Alberta", 2));
    std::shared_ptr<Card> CarteTest(new Card());
    std::shared_ptr<Card> cala(new Card("Alaska", Infantry));
    std::shared_ptr<Card> cterr(new Card("Territoires du Nord-Ouest", Cavalry));
    std::shared_ptr<Card> calb(new Card("Alberta", Artillery));
    listCountry.push_back(ala);
    listCountry.push_back(terr);
    listCountry.push_back(alb);
    listCard.push_back(cala);
    listCard.push_back(cterr);
    listCard.push_back(calb);

    // Tests getters setters
    {
        player1->addCard(cala);
        player1->addCard(cterr);
        player1->addCard(calb);
        player1->addCountry(ala);
        player1->addCountry(terr);
        player1->addCountry(alb);
        BOOST_CHECK_EQUAL(player1->getType(), HUMAN);
        BOOST_CHECK_EQUAL(player2->getId(), 2);
        player1->setName("Paul");
        player1->setStatus(LOSE);
        BOOST_CHECK_EQUAL(player1->getName(), "Paul");
        BOOST_CHECK_EQUAL(player2->getStatus(), PLAYING);
        BOOST_CHECK_EQUAL(player1->getStatus(), LOSE);
        for (int i = 0; i<3; i++){
            BOOST_CHECK_EQUAL(player1->getCardsList().at(i)->getName(),listCard.at(i)->getName());
            BOOST_CHECK_EQUAL(player1->getCountriesList().at(i)->getName(),listCountry.at(i)->getName());
        }
        BOOST_CHECK(player1->existCountry(Alberta));
        player1->deleteCard(calb);
        player1->deleteCountry(alb);
        for (int i = 0; i<2; i++){
            BOOST_CHECK_EQUAL(player1->getCardsList().at(i)->getName(),listCard.at(i)->getName());
            BOOST_CHECK_EQUAL(player1->getCountriesList().at(i)->getName(),listCountry.at(i)->getName());
        }
        BOOST_CHECK(!(player1->existCountry(Alberta)));

        std::string countryList[42] = {"Alaska", "Territoire du Nord-Ouest", "Alberta", "Ontario", "Groenland", "Quebec", "Ouest des Etat-Unis", "Est des Etats-Unis", "Amerique Centrale", "Venezuela", "Perou", "Bresil", "Argentine", "Afrique du Nord", "Egypte", "Afrique de l'Est", "Congo", "Afrique du Sud", "Madagascar", "Islande", "Grande-Bretagne", "Scandinavie", "Europe du Nord", "Ukraine", "Europe de l'Ouest", "Europe du Sud", "Moyen-Orient", "Afghanistan", "Ural", "Siberie", "Yakutsk", "Irkoutsk", "Mongolie", "Kamchatka", "Japon", "Chine", "Inde", "Siam", "Indonesie", "Nouvelle-Guinee", "Australie Orientale", "Australie Occidentale"};
        for (int i = 0; i < 42; i++){
            std::shared_ptr<Country> pays(new Country(countryList[i],i));
            player2->addCountry(pays);
        }
        BOOST_CHECK_EQUAL(player2->continentBonusTroop(), 38);
        std::vector<int> tab = {9,4,6,7,12,4};
        std::vector<int> result = player2->presenceOnContinents();
        for (int i = 0; i<6; i++) BOOST_CHECK_EQUAL(tab.at(i),tab.at(i));
        player2->print();
        BOOST_CHECK_EQUAL(player2->getOwnTroop(), 0);
    }
}