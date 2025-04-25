# ⛳ MINIGOLF

- Thử nghiệm game: 

# Giới thiệu game

Mini Golf là 1 tựa game 2D đánh golf với góc nhìn từ trên xuống.

Nhiệm vụ của bạn là vận dụng hết những tư duy vật lý của mình để khéo léo đánh bóng vào lỗ.

Rất nhiều thử thách thú vị đang chờ đợi bạn phía trước.

# 0. Cách tải game

Click Code (Green button) -> download file ZIP -> giải nén file ZIP

![Image](https://github.com/user-attachments/assets/2f140e83-a680-43c9-ba5b-f97141c0f9fa)

![Image](https://github.com/user-attachments/assets/6080bb7e-cde2-4fa3-90a5-3af2422a65d6)

# 1. Bắt đầu game

Click vào nút “PLAY” để bắt đầu chơi game.
<div style="text-align: center;">
  
![Image](https://github.com/user-attachments/assets/7298504b-cd63-4997-9ade-1354b85e9850)

</div>

Lúc này sẽ xuất hiên một button tường ứng với các màn chơi có độ khác khác nhau, người chơi click vào 1 trong các màn để bắt đầu chơi.

![Image](https://github.com/user-attachments/assets/43336e5d-f403-4d8e-853b-f65c250719ce)

# 2. Các thành phần trong game

## a. Ball (Bóng) ![Image](https://github.com/user-attachments/assets/9bb390bb-0738-4124-9550-36bc037ae664)

Là đối tượng chính mà người chơi điều khiển.

Người chơi tương tác bằng cách kéo chuột để điều chỉnh hướng và lực đánh (kéo càng xa thì đánh càng mạnh).

Khi thả chuột, bóng được bắn ra theo hướng ngược lại với hướng đã kéo.

Camera sẽ zoom theo hướng kéo để hỗ trợ nhắm chính xác.

## b. Hole (Lỗ) ![Image](https://github.com/user-attachments/assets/a557340d-12da-4e4c-83d2-268c0b368b5d)

Là điểm kết thúc của mỗi màn chơi.

Khi bóng được đánh vào lỗ, màn chơi được xem là hoàn thành.

Thường được đặt ở vị trí khó tiếp cận để tăng độ thử thách.

## c. Obstacle (Chướng ngại vật)

Mỗi màn chơi sẽ xuất hiện một số chướng ngại vật làm cản trở đường đi của bóng nhằm tạo thử thách cho người chơi.

Có thể cản bóng, làm đổi hướng và giảm lực của bóng khi bị va vào.

Đôi lúc, chướng ngại vật lại trở nên rất hữu ích nếu bạn biết vận dụng đúng cách.

## d. Teleport Portal (Cổng dịch chuyển)

Là cặp cổng Entry Portal và Exit Portal, dùng để dịch chuyển bóng từ vị trí này sang vị trí khác trong bản đồ.

Khi bóng chạm vào cổng vào (Entry portal), nó sẽ ngay lập tức xuất hiện tại vị trí của cổng ra (Exit portal).

Giữ nguyên hướng di chuyển và vận tốc hiện tại của bóng sau khi dịch chuyển, tạo cảm giác mượt mà và liên tục.

Người chơi có thể vận dụng để vượt những chướng ngại vật mà không thể đi qua.

## e. Map (Bản đồ)

Grass: là nơi bóng có thể di chuyển.

Sand: cũng là nơi bóng có thể di chuyển, nhưng sẽ khó di chuyển hơn do ma sát.

Water: nếu bóng rơi xuống nước, bạn sẽ bị coi là thua cuộc.

