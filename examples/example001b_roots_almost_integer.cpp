
#include <math/wide_decimal/decwide_t.h>

bool math::wide_decimal::example001b_roots_almost_integer()
{
  constexpr std::uint32_t wide_decimal_digits10 = UINT32_C(3001);

  using dec3001_t = math::wide_decimal::decwide_t<wide_decimal_digits10>;


  // http://mathreview.uwaterloo.ca/archive/voli/2/panju.pdf

  // Consider the amazing near-integer number:
  // N[((2/(27 + 3 Sqrt[69]))^(1/3) + (1/3) ((27 + 3 Sqrt[69])/2)^(1/3))^12345, 3000]
  // The exact page at Wolftam Alpha is:
  // https://www.wolframalpha.com/input/?i=N%5B%28%282%2F%2827+%2B+3+Sqrt%5B69%5D%29%29%5E%281%2F3%29+%2B+%281%2F3%29+%28%2827+%2B+3+Sqrt%5B69%5D%29%2F2%29%5E%281%2F3%29%29%5E12345%2C+3000%5D

  const dec3001_t term = dec3001_t(27U) + 3 * sqrt(dec3001_t(69));

  const dec3001_t p    = pow(cbrt(2 / term) + (cbrt(term / 2) / 3), 12345U);

  const dec3001_t control
  {
    "4."
    "1083022895549310191270112882918176489208718201648831275688755991422490601604513239332711953284142590"
    "0741185937620002995754672686524486145779055383899527263578330232012933385933991985216632576914976229"
    "2998193629160066989483686677769306772836456956975054925466092856746066077827717893116890246164372267"
    "4733453359923350482691376894254856446847040838738365261575226107104618160778327564014752956435353951"
    "8437870012135104624454178289956067621205451032259902708177416214788383434855938323690146067819608117"
    "5275036737534828585996243161255079595965411265468681581015496214481094557076188552193692195932586793"
    "9562843861818315218344916370194667025646456156114867567322597664338388915678392263411714886555273075"
    "6965353515289239455627522370006270862663143646244187443117154107939253458773680016597083975313743675"
    "2058777297826112411605459544091093918165212729896827451266153108816270502582715362098027786522409185"
    "2348661446313743617413681861539601802181873699132379847398511822700195785981741134605448132018960387"
    "3403024467637947467172463484503065372594179805114641754203685234645866387942126952654002947180879246"
    "4165389737056765401195778068335870320545352162951948027099275484839096890330339058074277208170872462"
    "1814921555103663916736739170525843138904506508039401508188667710311892624322969194067748989809324904"
    "5954819471672626788476301561279072723360273843457062345186711726306932827030433570241481905552308548"
    "4486111705086564826546459151580026765786859833103190255725162994654119649205306964213175421756857009"
    "5031082000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "0000000000000000000000000000000000000000000000000000000000002705215708320298616422113475265237749918"
    "3722522321242540666676440219942291840793929820757082882048164697285077119328507436125179979121999684"
    "5250084676906442985695595122284204619285122012621628347956320306152610487121173766466504972023263466"
    "0682596871607885468680429481545696849734053042883166505264032683507572805720727308615337781136904769"
    "0378468985716619871223961734395742359331859099910125692557876181113085776178941381917345923875727948"
    "4053258292330996133892311556348447296501914995608266692426447691709759031136319403405866513551854739"
    "3340761797165625937726437983717279510528131747096351396689226762212782842406212262581765782952810824"
    "1847740229696431710668108403030895073761198954115546649577650491980110989101795570918685050941247446"
    "E1507"
  };

  const dec3001_t closeness = fabs(1 - (p / control));

  const bool result_is_ok = closeness < (std::numeric_limits<dec3001_t>::epsilon() * 10);

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  const bool result_is_ok = math::wide_decimal::example001b_roots_almost_integer();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif