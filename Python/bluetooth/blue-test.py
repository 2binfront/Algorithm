import asyncio
from bleak import BleakScanner, BleakClient


async def discover_devices():
    scaner = BleakScanner()
    # 扫描附近的 BLE 设备
    devices = await scaner.discover()

    if not devices:
        print("没有找到蓝牙设备")
        return

    # 打印每个设备的基本信息
    for device in devices:
        if not device.name:
            continue
        print(f"设备名: {device.name}, 地址: {device.address}, 信号强度: {device.rssi}")

        # 获取设备的 GATT 服务及特征
        async with BleakClient(device.address) as client:
            print(f"\n连接到设备 {device.name} ({device.address})")

            # 获取设备的所有 GATT 服务
            services = await client.get_services()

            if not services:
                print("没有找到服务")
                continue

            for service in services:
                print(f" 服务: {service.uuid}")

                # 获取服务的特征
                for characteristic in service.characteristics:
                    print(f"   特征: {characteristic.uuid}")
                    # 你可以添加更多处理代码来读取特征值等
                    try:
                        value = await client.read_gatt_char(characteristic.uuid)
                        print(f"     特征值: {value}")
                    except Exception as e:
                        print(f"     读取特征值失败: {e}")
            print("\n")


# 运行
loop = asyncio.get_event_loop()
loop.run_until_complete(discover_devices())
