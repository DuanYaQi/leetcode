# Apex Mouse



## https://www.unknowncheats.me/forum/apex-legends/454800-universal-recoil-reducer-4.html

If you have a Logitech mouse, you can use the script in GHUB

```c++
function OnEvent(event, arg)
    if (event == "PROFILE_ACTIVATED") then
        EnablePrimaryMouseButtonEvents(true)
    end
 
    if (event == "MOUSE_BUTTON_PRESSED" and arg == 1)then
        if IsMouseButtonPressed(3)then
        repeat
            
        MoveMouseRelative(-5, 5)
        Sleep(10)
        MoveMouseRelative(5, -5)
        Sleep(10)
            
        until not IsMouseButtonPressed(1)
        end
    end
end
```

If you have a shitty PC like me I recommend LGS rather than GHUB



Capslock key to switch

```c++
EnablePrimaryMouseButtonEvents(true)
local recoil = false
function OnEvent(event, arg)
    if IsKeyLockOn("capslock") then
        if (event == "MOUSE_BUTTON_PRESSED" and arg == 1) then
            if IsMouseButtonPressed(3) then
                recoil=true
            end
        end
    end
 
    if recoil then
        repeat
        
        MoveMouseRelative(-10, 5)
        Sleep(20)
        MoveMouseRelative(10, -5)
        Sleep(20)
        
        until not IsMouseButtonPressed(1)
        recoil=false
    end
end
```

I think GHUB is relatively safe
It is difficult to automatically determine the nature of the script
It could be setting dpi，it could be displaying text

After all, that's what the gaming mouse is really all about.





顺便说一句，你是如何完成这项工作的？我将它设置为 GHUB 中的配置文件，并在 Scripts 下设置一个新脚本并将其复制粘贴并将其设置为持久配置文件。但它不会在鼠标按下或大写锁定时激活

实际上，没关系，当您移动鼠标并按住左 MB 时，它显然有效？



嗯，还是没有抖动。我可能没有正确设置它或其他什么。我在游戏中使用 600 DPI 和 1.8，也许这就是原因？我不知道，无论哪种方式，感谢您写这篇文章。

Are you launching GHUB/LGS as admin? 



经过大约半小时的测试，我无法让它看起来更接近视频之前/之后的 OP 中的结果（也就是说，如果您没有手动控制视频后的后坐力）。
可以使后坐力模式更小更容易控制，但仅此而已。
想知道是否有其他人运气更好，可以将其设置为类似于 OP 的结果。（使用 500 DPI、2 游戏内感知、1.0 ADS 进行测试）





This is for r6 but it also works here good however this is for my sensitivity and dpi so you may have to change yours. (this slightly reduces recoil )

这是针对 r6 的，但它在这里也很好用，但是这是针对我的灵敏度和 dpi，因此您可能需要更改您的。（这会稍微降低后坐力）

```c++
function OnEvent(event, arg)
    OutputLogMessage("event = %s, arg = %d\n", event, arg)
    
    if (event == "PROFILE_ACTIVATED") then
    	EnablePrimaryMouseButtonEvents(true)
    elseif event == "PROFILE_DEACTIVATED" then
    	ReleaseMouseButton(2) -- to prevent it from being stuck on
    end
        
    if (event == "MOUSE_BUTTON_PRESSED" and arg == 6) then
        recoil = not recoil
        spot = not spot
    end

    if (event == "MOUSE_BUTTON_PRESSED" and arg == 1 and recoil) then
        if recoil then
            repeat

            Sleep(25)
            MoveMouseRelative( 0, 1)
            Sleep(50)
            MoveMouseRelative( 0, 1)
            Sleep(100)
            MoveMouseRelative( 0, 1)
            Sleep(100)

            until not IsMouseButtonPressed(1)
        end
    end
end
```



```c++
EnablePrimaryMouseButtonEvents(true);

function OnEvent(event,arg)
    if IsKeyLockOn("numlock")then
        if IsMouseButtonPressed(3) then
            repeat
                if IsMouseButtonPressed(1) then
                	repeat
                    
                    MoveMouseRelative(5,-5)
                    Sleep(10)
                    MoveMouseRelative(-5,5)
                    Sleep(10)
                    MoveMouseRelative(5,0)
                    Sleep(10)
                    MoveMouseRelative(-5,-0)
                    Sleep(10)
                    
                    until not IsMouseButtonPressed(1)
                end
            until not IsMouseButtonPressed(3)
        end
    end
end
```





---

## https://www.unknowncheats.me/forum/apex-legends/445086-logitech-script-mice.html

```c++
EnablePrimaryMouseButtonEvents(true);

function OnEvent(event,arg)
    if IsKeyLockOn("scrolllock")then
        if IsMouseButtonPressed(3)then
            repeat
                if IsMouseButtonPressed(1) then
                    repeat
                    
                        MoveMouseRelative(1,2)
						Sleep(20)
                    
                    until not IsMouseButtonPressed(1)
                end
            until not IsMouseButtonPressed(3)
        end
    end
end
```



https://www.unknowncheats.me/forum/rainbow-six-siege/437833-tested-10-logitech-recoil-macro-scripts-cleanest.html

Step 1 - Have a logitech mouse, or G hub.

Step 2 - Open your ghub profile, click on your mouse image. On the profile you will see "details", then you will see scripting to the right of that. Click and open new script/edit.



Paste:

```c++
EnablePrimaryMouseButtonEvents (true);

function OnEvent(event,arg)
    if IsKeyLockOn("numlock")then
        if IsMouseButtonPressed(3)then
            repeat
            
                if IsMouseButtonPressed(1) then
                    repeat
                        MoveMouseRelative(0,1)
                        Sleep(5.0)  -- Change this for amount of recoil. 5 = my pubg/insurgency recoil. 13 is csgo. Less is more recoil accounting. 
                    until not IsMouseButtonPressed(1)
                end
                    
            until not IsMouseButtonPressed(3)
        end
    end
end
```



Really simple. Toggle **scolllock** or **numblock** to enable script (see third line of code). When your profile is enabled, right click enables, **right click + left click activates the script**.

```C++
EnablePrimaryMouseButtonEvents(true);

function OnEvent(event,arg)
    if IsKeyLockOn("scrolllock")then
        if IsMouseButtonPressed(3)then
            repeat
                if IsMouseButtonPressed(1) then
                    repeat
                    
                        MoveMouseRelative(0,5)
                        Sleep(9)
                    
                    until not IsMouseButtonPressed(1)
                end
            until not IsMouseButtonPressed(3)
        end
    end
end
```



`if IsKeyLockOn("scrolllock") then`
`if IsKeyLockOn("numlock") then`

`caplock` is a third option for enabling script.





## setting ghub

https://www.youtube.com/watch?v=sq4UGH_rDpo