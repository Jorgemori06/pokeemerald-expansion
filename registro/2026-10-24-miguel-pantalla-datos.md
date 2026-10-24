# 24/10/2026 · Miguel · Pantalla de datos del Pokémon

Rama: `miguel/pantalla-datos`

## Qué se ha hecho

- **IVs y EVs:** en la página de características, A pasa de características a IVs y a EVs, con el número exacto (opciones de la expansion `P_SUMMARY_SCREEN_IV_EV_INFO`, `_VALUES` y `_TILESET`; la última cambia la etiqueta de arriba).
- **Naturaleza:** detrás del nombre sale lo que sube y lo que baja ("(+Atq -AtE)" o "(neutra)"). Usa la naturaleza de la menta si la tiene, que es la que cuenta para las características.
- **Habilidades:** START en la página de información pasa por todas las habilidades de la especie (la oculta incluida), con su descripción y una etiqueta "Actual" / "Posible" / "Oculta" y "n/total".
- **Movimientos:** no hacía falta tocar nada; ya salen tipo, categoría, PP, potencia, precisión y descripción.

## Cómo se comprobó

- En el PC de Miguel no hay compilador: lo compila el CI. **No se ha visto en pantalla**, hay que probarlo en el emulador (que los textos quepan y se vean bien).

## Pendiente

- Probarlo jugando.
- Hacerla más bonita con gráficos nuevos: hay que dibujarlos y probarlos en el emulador.
- Avisar en pantalla de que START cambia de habilidad (ahora solo está en DUALOCKE).
