import subprocess

def switch_display(mode: str):
    mode_map = {
        '1': ('internal', '/internal'),  # 仅主屏幕（显示器1）
        '2': ('external', '/external'),  # 仅第二屏幕（显示器2）
        '3': ('clone', '/clone'),        # 复制屏幕
        '4': ('extend', '/extend'),      # 扩展显示
    }

    if mode not in mode_map:
        print("无效选项，请输入 1~4。")
        return

    mode_name, switch_arg = mode_map[mode]
    print(f"正在切换显示模式：{mode_name}")
    subprocess.run(['DisplaySwitch.exe', switch_arg])


def main():
    print("请选择显示模式：")
    print("1. 仅使用显示器1（/internal）")
    print("2. 仅使用显示器2（/external）")
    print("3. 复制显示器（/clone）")
    print("4. 扩展显示器（/extend）")
    
    user_input = input("请输入选项数字 (1~4): ").strip()
    switch_display(user_input)


if __name__ == '__main__':
    main()
