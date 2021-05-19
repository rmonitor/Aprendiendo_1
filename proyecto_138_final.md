# Aprendiendo_1
Conteo de carros subidos en plataforma y enviados a GPS particular
El funcionamiento es el siguiente:
Primera condición, si la plataforma (pison) esta activo, no debe hacer nada, esta plataforma es accionada manualmente en subida y en bajada, sino
Cuando un carro esta subido en la plataforma y es detectado por un detector de presencia (pulsador) y la plataforma (pison) se activa, realiza un ciclo completo
es decir subida y bajada y cuando ese carro lo quitamos de la plataforma, cuenta 1 y lanza a un gps a traves de rs232.
Según como colocamos un carro o dos, detectará y sumará 1 o 2 dependiendo de los detectores de presencia activados, si subimos un carro grande y pisa los 3 detectores
contará como un contenedor.
