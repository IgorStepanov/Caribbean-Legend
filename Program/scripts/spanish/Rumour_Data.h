#define SIMPLE_RUMOUR_NUM 95
#define CITIZEN_RUMOUR_NUM 10

string DEFAULT_TEXT[19] = {
    "Dicen que la Flota Dorada zarpa de Portobelo dos veces al año. Varias decenas de comerciantes protegidos por buques de guerra. Siempre hace la misma ruta: Va de Portobelo a La Habana y una vez que llega a Cuba navega hacia el norte rumbo al Viejo Mundo. Obviamente, las bodegas de la flota están llenas de tesoros sin medida.",
    "Nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, te diré.",
    "Es tranquilo por aquí. Los barcos no echan el ancla cerca a menudo, así que nada interesante que contar.",
    "La llegada de su nave, ¡de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda decirte algo especial, hace tiempo que no oigo noticias.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.",
    "Dicen que la Flota Dorada zarpa de Portobelo dos veces al año. Varias decenas de comerciantes protegidos por buques de guerra.  Siempre la misma ruta: de Porto Belo a La Habana, una vez que llega a Cuba, navega hacia el norte, hacia el Viejo Mundo. Obviamente, las bodegas de la flota están llenas de tesoros sin medida",
    "Nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, te diré.",
    "Esto está tranquilo. Los barcos no anclan cerca a menudo, así que no hay nada interesante que contaros.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda contarte nada especial, hace tiempo que no oigo ninguna noticia.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la pagará la gente corriente. Espero que no llegue aquí, ya tenemos suficientes problemas.",
    "Dicen que la Flota Dorada zarpa de Portobelo dos veces al año. Varias decenas de comerciantes protegidos por buques de guerra. Siempre hace la misma ruta: Va de Portobelo a La Habana y una vez que llega a Cuba navega hacia el norte rumbo al Viejo Mundo. Obviamente, las bodegas de la flota están llenas de tesoros sin medida.",
    "Nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, te diré.",
    "Es tranquilo por aquí. Los barcos no echan el ancla cerca a menudo, así que nada interesante que contaros.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "Dicen que la Flota Dorada zarpa de Portobelo dos veces al año. Varias decenas de comerciantes protegidos por buques de guerra. Siempre hace la misma ruta: Va de Portobelo a La Habana y una vez que llega a Cuba navega hacia el norte rumbo al Viejo Mundo. Obviamente, las bodegas de la flota están llenas de tesoros sin medida.",
};
/// Если новостей нет .
string NO_RUMOUR_TEXT[SIMPLE_RUMOUR_NUM] = {
    "No hay nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, te lo aseguro.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que no hay nada interesante que contar.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda decirle algo especial, hace tiempo que no oigo noticias.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.",
    "Nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, te lo aseguro.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que no hay nada interesante que contar.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda decirte algo especial, hace tiempo que no escucho ninguna noticia.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.",
    "Nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, te lo aseguro.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que nada interesante que contaros.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda contarte nada especial, hace tiempo que no oigo ninguna noticia.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.",
    "Nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, te lo aseguro.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que nada interesante que contaros.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda decirle algo especial, hace tiempo que no oigo noticias.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.",
    "Nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, te lo aseguro.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que no hay nada interesante que contar.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda decirle algo especial, hace tiempo que no oigo noticias.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.", // 30
    "Nada especial que contar. La vida transcurre tranquila y apacible. Sorprendentemente tranquila, ya te digo.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que nada interesante que contaros.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda decirle algo especial, hace tiempo que no oigo noticias.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.",
    "Nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, te lo aseguro.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que nada interesante que contaros.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda decirle algo especial, hace tiempo que no oigo noticias.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.",
    "Nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, ya te digo.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que nada interesante que contaros.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda decirle algo especial, hace tiempo que no oigo noticias.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.",
    "Nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, te lo aseguro.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que nada interesante que contaros.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda decirle algo especial, hace tiempo que no oigo noticias.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.",
    "Nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, te lo aseguro.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que no hay nada interesante que contar.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda decirle algo especial, hace tiempo que no oigo noticias.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.", // 60
    "Nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, te lo aseguro.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que nada interesante que contaros.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda decirle algo especial, hace tiempo que no oigo noticias.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.",
    "Nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, te lo aseguro.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que nada interesante que contaros.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda contarte nada especial, hace tiempo que no oigo ninguna noticia",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.",
    "Nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, te lo aseguro.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que nada interesante que contaros.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda decirle algo especial, hace tiempo que no oigo noticias.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.",
    "Nada especial que contar. La vida transcurre pacífica y tranquila. Sorprendentemente tranquila, te lo aseguro.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que nada interesante que contaros.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda decirle algo especial, hace tiempo que no oigo noticias.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.",
    "Nada especial que contar. La vida transcurre tranquila y apacible. Sorprendentemente tranquila, te diré.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que nada interesante que contaros.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda decirle algo especial, hace tiempo que no oigo noticias.",
    "Dicen que Europa va a estallar de nuevo. Se avecina una nueva guerra y, como siempre, la gente corriente la pagará. Espero que no llegue aquí, ya tenemos bastantes problemas.", // 90
    "Nada especial que contar. La vida transcurre tranquila y apacible. Sorprendentemente tranquila, te diré.",
    "Es tranquilo por aquí. Los barcos no anclan cerca a menudo, así que nada interesante que contaros.",
    "¡La llegada de su nave, de eso estamos hablando!",
    "No recuerdo nada de interés. Incluso las peleas de taberna son raras aquí.",
    "Dudo que pueda contarte nada especial, hace tiempo que no oigo noticias.",
};

// Слухи капитанов
string CAPTAIN_RUMOUR_TEXT[CITIZEN_RUMOUR_NUM] = {
    "Cuidado con los barcos casi hundidos. Algunos capitanes pueden prender fuego a sus propios suministros de pólvora, sólo para asestaros a ti y a tus aliados el último golpe del infierno. No es la forma más común de despedirse, pero ten cuidado de todos modos.",
    "¡No subestime las balas de cañón, capitán! Pueden parecer ordinarias y aburridas, pero tienen el mayor alcance y pueden infligir un daño decente a casi cualquier cosa. Y son baratas. Lo que siempre es bueno. No todo el mundo puede permitirse comprar bombas y disparos en cadena todo el tiempo.",
    "Cuidado con los barcos casi hundidos. Algunos capitanes pueden prender fuego a sus propios suministros de pólvora, sólo para asestaros a ti y a tus aliados el último golpe del infierno. No es la forma más común de despedirse, pero ten cuidado de todos modos.",
    "¡No subestime las balas de cañón, capitán! Pueden parecer ordinarias y aburridas, pero tienen el mayor alcance y pueden infligir un daño decente a casi cualquier cosa. Y son baratas. Lo que siempre es bueno. No todo el mundo puede permitirse comprar bombas y disparos en cadena todo el tiempo.",
    "Cuidado con los barcos casi hundidos. Algunos capitanes pueden prender fuego a sus propios suministros de pólvora, sólo para asestaros a ti y a tus aliados el último golpe del infierno. No es la forma más común de despedirse, pero ten cuidado de todos modos.",
    "¡No subestime las balas de cañón, capitán! Pueden parecer ordinarias y aburridas, pero tienen el mayor alcance y pueden infligir un daño decente a casi cualquier cosa. Y son baratas. Lo cual siempre es bueno. No todo el mundo puede permitirse comprar bombas y disparos en cadena todo el tiempo.",
    "Cuidado con los barcos casi hundidos. Algunos capitanes pueden prender fuego a sus propios suministros de pólvora, sólo para daros a ti y a tus aliados un último golpe desde el infierno. No es la forma más común de despedirse, pero ten cuidado de todos modos.",
    "¡No subestime las balas de cañón, capitán! Pueden parecer ordinarias y aburridas, pero tienen el mayor alcance y pueden infligir un daño decente a casi cualquier cosa. Y son baratas. Lo cual siempre es bueno. No todo el mundo puede permitirse comprar bombas y disparos en cadena todo el tiempo.",
    "Cuidado con los barcos casi hundidos. Algunos capitanes pueden prender fuego a sus propios suministros de pólvora, sólo para daros a ti y a tus aliados un último golpe desde el infierno. No es la forma más común de despedirse, pero ten cuidado de todos modos.",
    "¡No subestime las balas de cañón, capitán! Pueden parecer ordinarias y aburridas, pero tienen el mayor alcance y pueden infligir un daño decente a casi cualquier cosa. Y son baratas. Lo cual siempre es bueno. No todo el mundo puede permitirse comprar bombas y disparos en cadena todo el tiempo.",
};

// Слухи мещан мужские
string CITIZEN_MAN_RUMOUR_TEXT[CITIZEN_RUMOUR_NUM] = {
    "Comerciar puede ser una forma de hacer fortuna, sin embargo te sugiero que contrates a un sobrecargo, los negocios son complicados aquí, en las colonias. Sin un buen sobrecargo, te comerán a ti y a tus monedas. Así que tal vez deberías considerar trabajar para un gobernador o algo así. No es tan arriesgado y es muy honorable.",
    "Ve a una taberna si buscas algo en particular. No tengo nada que contarte.",
    "Comerciar puede ser una forma de hacer fortuna, sin embargo te sugiero que contrates a un sobrecargo, los negocios son complicados aquí, en las colonias. Sin un buen sobrecargo, te comerán a ti y a tus monedas. Así que tal vez deberías considerar trabajar para un gobernador o algo así. No es tan arriesgado y es muy honorable.",
    "Ve a una taberna si buscas algo en particular. No tengo nada que contarte.",
    "Comerciar puede ser una forma de hacer fortuna, sin embargo te sugiero que contrates a un sobrecargo, los negocios son complicados aquí, en las colonias. Sin un buen sobrecargo, te comerán a ti y a tus monedas. Así que tal vez deberías considerar trabajar para un gobernador o algo así. No es tan arriesgado y es muy honorable.",
    "Ve a una taberna si buscas algo en particular. No tengo nada que contarte.",
    "Comerciar puede ser una forma de hacer fortuna, sin embargo te sugiero que contrates a un sobrecargo, los negocios son complicados aquí, en las colonias. Sin un buen sobrecargo, te comerán a ti y a tus monedas. Así que tal vez deberías considerar trabajar para un gobernador o algo así. No es tan arriesgado y es muy honorable.",
    "Ve a una taberna si buscas algo en particular. No tengo nada que contarte.",
    "El comercio puede ser una forma de hacer fortuna, sin embargo te sugiero que contrates a un sobrecargo, el negocio es complicado aquí, en las colonias. Sin un buen sobrecargo, te comerán a ti y a tus monedas. Así que tal vez deberías considerar trabajar para un gobernador o algo así. No es tan arriesgado y es muy honorable.",
    "Ve a una taberna si buscas algo en particular. No tengo nada que contarte.",
};

// Слухи мещан женские
string CITIZEN_WOMAN_RUMOUR_TEXT[CITIZEN_RUMOUR_NUM] = {
    "Si no puedes contratar suficiente gente en las tabernas, busca en las calles. A veces hay marineros vagando por la ciudad, buscando al capitán adecuado.",
    "¡Este lugar es bárbaro! Sobre todo. Los hombres locales son brutos sin honor. Por favor, no ignoren a las mujeres que necesitan ayuda. Tenemos tan pocos protectores aquí. Muestren algo de dignidad!",
    "Si no puedes contratar suficiente gente en las tabernas, busca en las calles. A veces hay marineros vagando por la ciudad, buscando al capitán adecuado.",
    "¡Este lugar es bárbaro! Sobre todo. Los hombres locales son brutos sin honor. Por favor, no ignoren a las mujeres que necesitan ayuda. Tenemos tan pocos protectores aquí. Muestren algo de dignidad!",
    "Si no puedes contratar suficiente gente en las tabernas, busca en las calles. A veces hay marineros vagando por la ciudad, buscando al capitán adecuado.",
    "¡Este lugar es bárbaro! Sobre todo. Los hombres locales son brutos sin honor. Por favor, no ignoren a las mujeres que necesitan ayuda. Tenemos tan pocos protectores aquí. Muestren algo de dignidad!",
    "Si no puedes contratar suficiente gente en las tabernas, busca en las calles. A veces los marineros vagan por la ciudad, buscando al capitán adecuado.",
    "¡Este lugar es una barbaridad! Sobre todo. Los hombres locales son brutos sin honor. Por favor, no ignoren a las mujeres que necesitan ayuda. Aquí tenemos muy pocos protectores. Muestren algo de dignidad",
    "Si no puedes contratar suficiente gente en las tabernas, busca en las calles. A veces los marineros vagan por la ciudad, buscando al capitán adecuado.",
    "¡Este lugar es bárbaro! Sobre todo. Los hombres locales son brutos sin honor. Por favor, no ignoren a las mujeres que necesitan ayuda. Aquí tenemos muy pocos protectores. ¡Muestren algo de dignidad!",
};

// Слухи дворян
string NOBLE_MAN_RUMOUR_TEXT[CITIZEN_RUMOUR_NUM] = {
    "Domine su estoque, señor. Le salvará la vida y protegerá su honor. Pero, para ser completamente honesto, los malvivientes locales no se merecen un estoque, sino un hacha.",
    "Ten siempre suficiente pólvora y balas a tu disposición. No querrás quedarte sin munición en medio de una pelea. También estaría bien tener un arma extra. Esas cosas suelen explotar...",
    "Domine su estoque, señor. Le salvará la vida y protegerá su honor. Pero, para ser completamente honesto, los malvivientes locales no se merecen un estoque, sino un hacha.",
    "Ten siempre suficiente pólvora y balas a tu disposición. No querrás quedarte sin munición en medio de una pelea. También estaría bien tener un arma extra. Esas cosas suelen explotar...",
    "Domine su estoque, señor. Le salvará la vida y protegerá su honor. Pero, para ser completamente honesto, los malvivientes locales no se merecen un estoque, sino un hacha.",
    "Ten siempre suficiente pólvora y balas a tu disposición. No querrás quedarte sin munición en medio de una pelea. También estaría bien tener un arma extra. Esas cosas suelen explotar...",
    "Domine su estoque, señor. Le salvará la vida y protegerá su honor. Pero, para ser completamente honesto, los malvivientes locales no se merecen un estoque, sino un hacha.",
    "Ten siempre suficiente pólvora y balas a tu disposición. No querrás quedarte sin munición en medio de una pelea. También estaría bien tener un arma extra. Esas cosas suelen explotar...",
    "Domine su estoque, señor. Le salvará la vida y protegerá su honor. Pero, para ser completamente honesto, los malvivientes locales no se merecen un estoque, sino un hacha.",
    "Ten siempre suficiente pólvora y balas a tu disposición. No querrás quedarte sin munición en medio de una pelea. También estaría bien tener un arma extra. Esas cosas suelen explotar...",
};

// Слухи дворянок
string NOBLE_WOMAN_RUMOUR_TEXT[CITIZEN_RUMOUR_NUM] = {
    "Pareces un hombre de honor. Un hombre noble. Si fueras de otro tipo, te enviaría a una taberna a preguntar a la gente de allí",
    "¿Sabía usted, capitán, que hay todo tipo de objetos mágicos por esta zona? Puede que la Iglesia no lo apruebe, pero todo el mundo usa talismanes y amuletos.",
    "Pareces un hombre de honor. Un hombre noble. Si fueras de otro tipo, te enviaría a una taberna a preguntar a la gente de allí",
    "¿Sabía usted, capitán, que hay todo tipo de objetos mágicos por esta zona? Puede que la Iglesia no lo apruebe, pero todo el mundo usa talismanes y amuletos.",
    "Pareces un hombre de honor. Un hombre noble. Si fueras de otro tipo, te enviaría a una taberna a preguntar a la gente de allí",
    "¿Sabía usted, capitán, que hay todo tipo de objetos mágicos por esta zona? Puede que la Iglesia no lo apruebe, pero todo el mundo usa talismanes y amuletos.",
    "Pareces un hombre de honor. Un hombre noble. Si fueras de otro tipo, te enviaría a una taberna a preguntar a la gente de allí",
    "¿Sabía usted, capitán, que hay todo tipo de objetos mágicos por esta zona? Puede que la Iglesia no lo apruebe, pero todo el mundo usa talismanes y amuletos.",
    "Pareces un hombre de honor. Un hombre noble. Si fueras de otro tipo, te enviaría a una taberna a preguntar a la gente de allí",
    "¿Sabía usted, capitán, que hay todo tipo de objetos mágicos por esta zona? Puede que la Iglesia no lo apruebe, pero todo el mundo usa talismanes y amuletos.",
};

// Слухи матросов
string SAILOR_RUMOUR_TEXT[CITIZEN_RUMOUR_NUM] = {
    "Es difícil encontrar un capitán decente hoy en día. La mayoría quieren que seamos sus soldados o esclavos. O ambas cosas. Que se jodan. Espero que tú seas diferente.",
    "Nada interesante. La cosa será interesante cuando se acaben nuestros suministros.",
    "Es difícil encontrar un capitán decente en estos días. La mayoría quieren que seamos sus soldados o esclavos. O ambas cosas. Que se jodan. Espero que tú seas diferente.",
    "Nada interesante. La cosa será interesante cuando se acaben nuestros suministros.",
    "Es difícil encontrar un capitán decente en estos días. La mayoría quieren que seamos sus soldados o esclavos. O ambas cosas. Que se jodan. Espero que tú seas diferente.",
    "Nada interesante. La cosa será interesante cuando se acaben nuestros suministros.",
    "Es difícil encontrar un capitán decente en estos días. La mayoría quieren que seamos sus soldados o esclavos. O ambas cosas. Que se jodan. Espero que tú seas diferente.",
    "Nada interesante. La cosa será interesante cuando se acaben nuestros suministros.",
    "Es difícil encontrar un capitán decente en estos días. La mayoría quieren que seamos sus soldados o esclavos. O ambas cosas. Que se jodan. Espero que tú seas diferente.",
    "Nada interesante. La cosa se pondrá interesante cuando se nos acaben las provisiones.",
};

// Если новостей нет в LSC
string NO_RUMOUR_LSC_TEXT[5] = {
    "Esto está bastante aburrido. ¿Qué noticias te interesa oír?",
    "¿Cotilleos? Nada que contaros, estaremos bien hasta que Rivados y Narwals vuelvan a pelearse.",
    "Nada interesante... Será interesante cuando se nos acaben los víveres.",
    "Lo mismo de siempre. Aburrido. Tal vez los piratas le pateen el culo a los clanes. Eso sí que pondrá de buen humor.",
    "Sin noticias, sin chismes. Hasta que los clanes empiecen a matarse entre ellos, claro.",
};
