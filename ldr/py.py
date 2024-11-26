import spidev
import time

# Configurar SPI
spi = spidev.SpiDev()  # Crear un objeto SPI
spi.open(0, 0)         # Abrir SPI en el bus 0, dispositivo 0
spi.max_speed_hz = 1000000  # Configurar la velocidad de SPI

# Leer del MCP3008
def read_channel(channel):
    if channel < 0 or channel > 7:
        raise ValueError("El canal debe estar entre 0 y 7.")
    
    # Enviar solicitud al MCP3008
    adc = spi.xfer2([1, (8 + channel) << 4, 0])
    
    # Convertir los datos recibidos
    data = ((adc[1] & 3) << 8) + adc[2]
    return data

try:
    while True:
        # Leer el valor del canal 0
        value = read_channel(0)
        print(f"Valor del canal 0: {value}")
        time.sleep(0.5)  # Esperar 500 ms

except KeyboardInterrupt:
    print("\nTerminando...")
finally:
    spi.close()  # Cerrar SPI al finalizar
