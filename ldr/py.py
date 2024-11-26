import spidev

# Configurar SPI
spi = spidev.SpiDev()
spi.open(0, 0)
spi.max_speed_hz = 1000000

# Prueba de bucle SPI
def loopback_test():
    send_data = [0x01, 0x80, 0x00]  # Datos arbitrarios
    received_data = spi.xfer2(send_data)
    print(f"Enviado: {send_data}")
    print(f"Recibido: {received_data}")

try:
    loopback_test()
finally:
    spi.close()
