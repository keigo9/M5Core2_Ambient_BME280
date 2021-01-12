import serial
import ambient
if __name__ == '__main__':

    # Arduinoの接続ポート
    # PORT = '各自の接続ポート'
    PORT = 'COM4'
    ser = serial.Serial(PORT, 9800)

    # チャネルID
    # CHANNEL_ID = 自分のチャネルID
    CHANNEL_ID = hoge

    # ライトキー
    # WRITE_KEY = "自分のライトキー"
    WRITE_KEY = "hogehoge"

    data = []
    flag = False

    while True:
        message = ser.readline().decode('utf-8', errors='ignore').replace('\n', '')
        if(message == 'START'):
            flag = True
        elif(message == 'END'):
            flag = False
            ambi = ambient.Ambient(CHANNEL_ID, WRITE_KEY)
            # データが1つのとき
            # r = ambi.send({"d1": data[0]})
            # データが複数のとき
            # print(data)
            r = ambi.send({"d1": data[0], "d2": data[1], "d3": data[2]})
            print(r)
            data = []
        else:
            if(flag):
                print(message)
                data.append(message)
