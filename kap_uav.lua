--[[
  KAP UAV Exposure Control Script v3.8

  Licence: GPL (c) 2013, 2014, 2015, 2016 by waterwingz
  -- with contributions from wayback/peabody & Naccio
  Please check for the latest version (and documentation) at :
     http://chdk.wikia.com/wiki/KAP_%26_UAV_Exposure_Control_Script

@title KAP UAV 3.8 Beta
@chdk_version 1.3

@param     i Shot Interval (sec)
  @default i 7
  @values  i Burst Fast 2 3 4 5 10 15 20 30 45 60 90 120 180 240 300

@param     o Shutdown (minutes, 0=never)?
  @default o 0
  @range   o 0 240
@param     s Total Shots (0=infinite)
  @default s 0
  @range   s 0 10000
@param     j Power off when done?
  @default j 0
  @range   j 0 1
@param     b Display Off?
  @default b 0
  @values  b No Yes Delayed
@param     d Start Delay Time (sec)
  @default d 0
  @range   d 0 60000

@param     g Exposure Bracketing
  @default g 0
  @values  g Off +/-0.33 +/-0.66 +/-1.00 +/-1.33 +/-1.66 +/-2.00
@param     e Exposure Comp (stops)
  @default e 6
  @values  e -2.0 -1.66 -1.33 -1.0 -0.66 -0.33 0.0 0.33 0.66 1.00 1.33 1.66 2.00
@param     z Zoom position
  @default z 0
  @values  z Off 0% 10% 20% 30% 40% 50% 60% 70% 80% 90% 100%
@param     c Focus @ Infinity
  @default c 0
  @range   c 0 1

@param     y Tv Min (sec)
  @default y 0
  @values  y None 1/60 1/100 1/200 1/400 1/640 1/800 1/1000 1/1250 1/1600 1/2000
@param     t Target Tv (sec)
  @default t 5
  @values  t 1/100 1/200 1/400 1/640 1/800 1/1000 1/1250 1/1600 1/2000 1/5000
@param     x Tv Max (sec)
  @default x 3
  @values  x 1/1000 1/1250 1/1600 1/2000 1/5000 1/10000
@param     f Av Low(f-stop)
  @default f 4
  @values  f 1.8 2.0 2.2 2.6 2.8 3.2 3.5 4.0 4.5 5.0 5.6 6.3 7.1 8.0
@param     a Av Target (f-stop)
  @default a 7
  @values  a 1.8 2.0 2.2 2.6 2.8 3.2 3.5 4.0 4.5 5.0 5.6 6.3 7.1 8.0
@param     m Av Max (f-stop)
  @default m 13
  @values  m 1.8 2.0 2.2 2.6 2.8 3.2 3.5 4.0 4.5 5.0 5.6 6.3 7.1 8.0
@param     p ISO Min
  @default p 1
  @values  p 80 100 200 400 800 1250 1600
@param     q ISO Max1
  @default q 2
  @values  q 100 200 400 800 1250 1600
@param     r ISO Max2
  @default r 3
  @values  r 100 200 400 800 1250 1600
@param     n Allow use of ND filter?
  @default n 1
  @values  n No Yes

@param     v Video Interleave (shots)
  @default v 0
  @values  v Off 1 5 10 25 50 100
@param     w Video Duration (sec)
  @default w 10
  @range   w 5 300

@param     u USB Shot Control?
  @default u 0
  @values  u None On/Off OneShot GntWire Pixhawk
@param     k USB Timeout (secs 0=off)
  @default k 0
  @range   k 0 240
@param     h Shot Sync LED
 @default  h 0
 @values   h Off 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

@param     l Logging
  @default l 3
  @values  l Off Screen SDCard Both

Spares : none

--]]

    props=require("propcase")
    capmode=require("capmode")
    cfg1=require("gen/cnf_core")
    cfg2=require("gen/cnf_osd")

-- convert user parameter to usable variable names and values
    tv_table        = { -320, 576, 640, 736, 832, 896, 928, 960, 992, 1024, 1056, 1180, 1276}
    tv96target      = tv_table[t+3]
    tv96max         = tv_table[x+8]
    tv96min         = tv_table[y+1]
    sv_table        = { 381, 411, 507, 603, 699, 761, 795 }             -- ISO market to sv96 real
    sv96min         = sv_table[p+1]
    sv96max1        = sv_table[q+2]
    sv96max2        = sv_table[r+2]
    av_table        = { 171, 192, 218, 265, 285, 322, 347, 384, 417, 446, 477, 510, 543, 576 }
    av96target      = av_table[a+1]
    av96minimum     = av_table[f+1]
    av96max         = av_table[m+1]
    ec96adjust      = (e - 6)*32
    bracketing      = g*32
    video_table     = { 0, 1, 5, 10, 25, 50, 100 }
    video_mode      = video_table[v+1]
    video_duration  = w*1000
    intervals       = { 0, 1, 2, 3, 4, 5, 10, 15, 20, 30, 45, 60, 90, 120, 180, 240, 300 }
    interval        = intervals[i+1]*1000
    poff_if_done    = j
    start_delay     = d
    max_shots       = s
    backlight_saver = b
    log_mode        = l
    focus_at_infinity = c
    usb_mode        = u
    usb_timeout     = k*1000
    usb_precision   = 1                                                -- 1 mSec precision USB timer for PWM modes
    sync_led        = h
    if ( z==0 ) then zoom_setpoint = nil  else zoom_setpoint = (z-1)*10 end
    if ( o==0 ) then script_timeout = 0 else script_timeout = get_tick_count() + o*60000 end

-- constants
    USB_MODE_None    = 0
    USB_MODE_On_Off  = 1
    USB_MODE_OneShot = 2
    USB_MODE_GntWire = 3
    USB_MODE_Pixhawk = 4
    USB_SLEEP = 0
    USB_IDLE = 1
    USB_SHOOTING = 2
    LED_BLINK_TIME = 50                                                -- time in mSec for sync LED to flash (in continuous mode)

-- initial configuration values
    nd96offset=3*96                                                    -- ND filter's number of equivalent f-stops  (f * 96)
    infx = 50000                                                       -- focus lock distance in mm (approximately 55 yards)
    shot_count = 0                                                     -- shot counter
    old_console_timeout = get_config_value(cfg2.console_timeout)
    usb_shooting_mode = USB_SLEEP                                      -- pwm controlled shooting mode 0=sleep,  1=idle,  2=shooting
    script_exit = false                                                -- flag to indicate it's time to shutdown the script
    msec_time_stamp = nil                                              -- precision time stamp - will be logged if not nil
    old_remote_mode = 0                                                -- holder for USB remote mode at startup
    in_continuous_mode = false                                         -- continuous shooting mode state
    pwm_halted=false                                                   -- true when continuous shooting mode has failed
    drive_mode = get_prop(props.DRIVE_MODE)                            -- Canon shooting drive mode (0=single, 1=continuous, 2=timer?)
    if(backlight_saver==2) then
        blite_timer = get_tick_count()+30000                           -- backlight initial off delay in mSec
    else
        blite_timer = get_tick_count()                                 -- backlight off immediately
    end
    usb_wait_message = "Waiting on USB. Press MENU to exit"

    -- focus modes
    sd_modes = get_sd_over_modes()                                     -- get camera's available MF modes
    if ( focus_at_infinity == 0 ) then
        sd_ovr_mode_str ="OFF"
    else
        if ( sd_modes == 0 ) then                                      -- no SD override capability
            sd_ovr_mode_str ="???"
        elseif ( bitand(sd_modes, 0x02 ) ~=0 ) then                    -- first choice = AFL
            sd_ovr_mode_str = "AFL"
        elseif ( bitand(sd_modes, 0x04) ~= 0 ) then                    -- second choice = MF
            sd_ovr_mode_str = "MF"
        elseif ( bitand(sd_modes, 0x01 ) ~= 0 ) then                   -- third choice = AF
            sd_ovr_mode_str = "AF"
        end
    end

     -- check camera Av configuration ( variable aperture and/or ND filter )
    if n==0 then                                                       -- use of nd filter allowed?
        if get_nd_present()==1 then                                    -- check for ND filter only
            Av_mode = 0                                                -- 0 = ND disabled and no iris available
        else
            Av_mode = 1                                                -- 1 = ND disabled and iris available
        end
    else
        Av_mode = get_nd_present()+1                                   -- 1 = iris only , 2=ND filter only, 3= both ND & iris
    end

-- UI Functions

function lprintf(...)
    if ( log_mode ~= 0) then
        local str=string.format(...)
        if ( log_mode > 1 ) then
            if msec_time_stamp == nil then
                log_custom_buffer = log_custom_buffer..os.date("%Y%b%d %X    ")..string.format(...).."\n"
            else
                log_custom_buffer = log_custom_buffer..msec_time_stamp..string.format(...).."\n"
            end
        end
    end
end

function printf(...)
    if ( log_mode ~= 0) then
        local str=string.format(...)
        if (( log_mode == 1) or (log_mode == 3)) then print(str) end
        lprintf(...)
    end
end

function draw_message_string(str)
    draw_string( 16, 144+64, string.sub(str.."                          ",0,42), 258, 259)
end

log_write_time = 0                                                     -- log write delay in seconds increments
log_custom_buffer=""

function write_log_to_disk()                                           -- returns -1 on failure,  0 on not enable,  1 on success
    local rc = 0
    if ( log_mode > 1 ) then
        local logname="A/KAP.log"
        log=io.open(logname,"a")
        if (log~=nil) then
            lprintf("Logger : log file updated.")
            log:write(log_custom_buffer)
            log:close()
            log_custom_buffer = ""
            log_write_time = get_tick_count()+60000
            rc = 1
        else
            lprintf("Logger : SD card busy. Unable to update log.")
            log_write_time = get_tick_count()+10000
            rc = -1
        end

    end
    return rc
end

tv_ref = {    -- note : tv_ref values set 1/2 way between shutter speed values
-608, -560, -528, -496, -464, -432, -400, -368, -336, -304,
-272, -240, -208, -176, -144, -112,  -80,  -48,  -16,   16,
  48,   80,  112,  144,  176,  208,  240,  272,  304,  336,
 368,  400,  432,  464,  496,  528,  560,  592,  624,  656,
 688,  720,  752,  784,  816,  848,  880,  912,  944,  976,
1008, 1040, 1072, 1096, 1129, 1169, 1192, 1225, 1265, 1376  }

tv_str = {
       ">64",
        "64",    "50",    "40",    "32",    "25",    "20",    "16",    "12",     "10",   "8.0",
       "6.0",   "5.0",   "4.0",   "3.2",   "2.5",   "2.0",   "1.6",   "1.3",    "1.0",   "0.8",
       "0.6",   "0.5",   "0.4",   "0.3",   "1/4",   "1/5",   "1/6",   "1/8",   "1/10",  "1/13",
      "1/15",  "1/20",  "1/25",  "1/30",  "1/40",  "1/50",  "1/60",  "1/80",  "1/100", "1/125",
     "1/160", "1/200", "1/250", "1/320", "1/400", "1/500", "1/640", "1/800", "1/1000","1/1250",
    "1/1600","1/2000","1/2500","1/3200","1/4000","1/5000","1/6400","1/8000","1/10000","hi"  }

function print_tv(val)
    if ( val == nil ) then return("-") end
    local i = 1
    while (i <= #tv_ref) and (val > tv_ref[i]) do i=i+1 end
    return tv_str[i]
end

av_ref = {     160, 176,   208,  243,  275,  304,  336,  368,  400,  432,  464,  480,  496,  512,  544,  592,  624,   656,   688,   720,  752,   784 }
av_str = {"n/a","1.8", "2.0","2.2","2.6","2.8","3.2","3.5","4.0","4.5","5.0","5.6","5.9","6.3","7.1","8.0","9.0","10.0","11.0","13.0","14.0","16.0","hi"}

function print_av(val)
    if ( val == nil ) then return("-") end
    local i = 1
    while (i <= #av_ref) and (val > av_ref[i]) do i=i+1 end
    return av_str[i]
end

sv_ref = {  310, 370,  397,  424,  456,  492,  523,  555,  588,  619,  651,  684,  731,   779,   843,   907   }
sv_str = {"lo(","50","80","100","120","160","200","250","320","400","500","640","800","1250","1600","3200","hi"}

function print_sv(val)
    if ( val == nil ) then return("-") end
    local i = 1
    while (i <= #sv_ref) and (val > sv_ref[i]) do i=i+1 end
    if (i==1) then return sv_str[i]..val..")" end
    return sv_str[i]
end

-- wait for a CHDK function to be true/false with a timeout
function wait_timeout(func , state, interval, delay, msg)
    local timestamp = get_tick_count()
    local timeout = false
    repeat
        sleep(delay)
        timeout = get_tick_count() > timestamp + interval
    until (func() == state ) or timeout
    if timeout and (msg ~= nil) then printf(msg) end
    return timeout
end

-- switch between shooting and playback modes
function switch_mode( mode )
    if ( mode == 1 ) then                                              -- go to playback or shooting mode ?
        if ( get_mode() ~= false ) then return end                     -- exit if already in shooting mode
        set_record(1)                                                  -- switch to shooting mode
        wait_timeout( get_mode, true, 10000, 100, "Fault on switch to shooting mode")
    else
        if ( get_mode() ~= true ) then return end                      -- exit if already in playback mode
        set_record(0)                                                  -- switch to playback mode
        wait_timeout( get_mode, false, 10000, 100, "Fault on switch to playback mode")
    end
    sleep(2000)                                                        -- add a little extra delay so things like set_LCD_display() don't crash on some cameras
    lprintf("Mode switched to "..capmode.get_name())
end

-- focus lock and unlock
function lock_focus()
    if ((focus_at_infinity~=0) and (bitand(sd_modes, 0x07)~=0)) then   -- focus lock at infinity requested and SD override is possible with this camera?
        if ( bitand(sd_modes, 0x02) ~= 0 ) then                        -- attempt AFL first
            set_aflock(1)
        elseif ( bitand(sd_modes, 0x04) ~= 0 ) then                    -- otherwise try for MF
            set_mf(1)
            if (get_prop(props.FOCUS_MODE) ~= 1) then printf("Warning:MF enable failed***") end
        end
        if (sd_modes>0) then
            sleep(1000)
            set_focus(infx)
            sleep(1000)
        end
    end
end

function unlock_focus()
    if (focus_at_infinity~=0) then                                     -- focus lock at infinity requested ?
        if ( bitand(sd_modes, 0x02) ~=0 ) then                         -- was AFL used ?
            set_aflock(0)
        elseif ( bitand(sd_modes, 0x04) ~= 0 ) then                    -- or maybe MF ?
            set_mf(0)
        end
    end
end

-- zoom position
function update_zoom(zpos)
    local count = 0
    if(zpos ~= nil) then
        zstep=((get_zoom_steps()-1)*zpos)/100
        printf("setting zoom to "..zpos.." percent step="..zstep)
        sleep(200)
        set_zoom(zstep)
        sleep(2000)
        press("shoot_half")
        wait_timeout( get_shooting, true, 2000, 100, "Unable to focus after zoom")
        release("shoot_half")
    end
end

-- restore camera settings on shutdown
function restore()
    local rc=0
    set_config_value(cfg1.remote_enable,old_remote_mode)               -- USB remote reset
    set_config_value(cfg2.console_timeout,old_console_timeout)         -- restore console timeout value
    rc = write_log_to_disk()                                           -- update log
    set_draw_title_line(1)
    set_exit_key("shoot_full")
    if (backlight_saver>0) then set_lcd_display(1) end                 -- display on
    unlock_focus()
    if(rc == -1) then                                                  -- retry log write?
        sleep(2000)
        write_log_to_disk()
    end
    if ( poff_if_done == 1 ) then                                      -- complete power down ?
            printf("power off - shot count at limit")
            sleep(2000)
            post_levent_to_ui('PressPowerButton')
            sleep(5000)
    end
    switch_mode(0)                                                     -- exit shooting mode and hopefully retract lens (if delay = 0)
end

--  ========================== Video mode =================================

function shoot_video()
    local capture_mode
    unlock_focus()
    printf("Video recording started.")
    if( video_button ) then
        click "video"
    else
        capture_mode=capmode.get()
        capmode.set('VIDEO_STD')
        sleep(1000)
        press("shoot_full")
        sleep(500)
        release("shoot_full")
    end
    local end_second = get_tick_count() + video_duration
    repeat
        wait_click(500)
    until (is_key("menu")) or (get_tick_count() > end_second)
    if( video_button ) then
        click "video"
    else
        press("shoot_full")
        sleep(500)
        release("shoot_full")
        sleep(2000)
        capmode.set(capture_mode)
    end
    printf("Video recording stopped.")
    sleep(2000)
    set_prop(props.FLASH_MODE, 2)                                      -- flash off again
    set_prop(props.AF_ASSIST_BEAM,0)                                   -- AF assist off again
    lock_focus()
    local nxshot_time = get_tick_count()
    while ( next_shot_time <= nxshot_time ) do next_shot_time = next_shot_time + interval end
end

--  ========================== PWM USB Pulse Controlled Functions =================================
--   (sample code for Gentles gentWIRE-USB2 and for direct pixhawk flight controller connection)

    PWM_required_repeats = 0                                           -- set this to the number of times the same pulse must repeat before something happens
    previous_command = "none"
    repeat_count = 0

function flush_usb_buffers()
    get_usb_power(0)                                                   -- flush the USB buffer
    repeat until get_usb_power(2) == 0
end

function wait_for_usb_active()                                         -- wait for USB signal of some sort
    local usb_active = false
    flush_usb_buffers()
    printf("waiting on USB signal")
    repeat
        draw_message_string(usb_wait_message)
        wait_click(100)
        if ( usb_mode ~= USB_MODE_Pixhawk) then
            usb_active = (get_usb_power(1) == 1) or (get_usb_power(2) > 0)
        else
            usb_active = wait_for_shoot_pulse(250)                     -- pixhawk only
        end
    until (usb_active or is_key("menu"))
    return(usb_active)
end

    function repeat_check(command,p)                                   -- check for and process repeated pulses - returns the number of sequential repeats of the current pulse
        if (command ~= previous_command ) then
            if ( repeat_count > 0 ) then
                printf(previous_command.." repeated "..repeat_count.." times")
            end
            previous_command=command
            repeat_count = 0
            printf(" * usb pulse = "..command.." ("..p.." mSec)")
        else
            repeat_count = repeat_count+1
        end
        return (repeat_count)
    end

    function wait_for_shoot_pulse(timeout)                             -- pixhawk only
        local pw=0
        local tmo=get_tick_count()+timeout                             -- set timeout expiry
        repeat                                                         -- tight loop waiting pulses
            pw = get_usb_power(2) * usb_precision
            if pw>0 then
                if pw>1 and pw<5 then
                    repeat_check("start pulse ",pw)
                    return(true)                                       -- return on 3 mSec pulse  (2,3, or 4 allowed)
                else repeat_check("idle pulse ",pw) end                -- log a count of other pulses
            end
        until get_tick_count() > tmo                                   -- time out?
        return(false)
    end

    -- <<pixhawk routines start here>>

        function pwm1(pwidth)
            if( repeat_check("pwm1 shoot",pwidth ) >= PWM_required_repeats ) then
               usb_shooting_mode = USB_SHOOTING                        -- request the next shot
            end
        end

        function pwm2(pwidth)
            if( repeat_check("pwm2 idle",pwidth ) >= PWM_required_repeats ) then
              --usb_shooting_mode = USB_IDLE                           -- neutral position - do nothing
            end
        end

        function pwm3(pwidth)
            if( repeat_check("pwm3 idle",pwidth ) >= PWM_required_repeats ) then
            end
        end

        function pwm4(pwidth)
            repeat_check("shutdown",pwidth)
            restore()
            shut_down()
        end

    -- <<pixhawk routines end>>

    -- << gentwire-USB2 routines start here>>

        function ch1up(pwidth)
            if( repeat_check("ch1up",pwidth ) >= PWM_required_repeats ) then
                usb_shooting_mode = USB_SHOOTING                       -- request the next shot
            end
        end

        function ch1mid(pwidth)
            if( repeat_check("ch1mid",pwidth ) >= PWM_required_repeats ) then
              -- blah                                                  -- neutral position - do nothing
            end
        end

        function ch1down(pwidth)
            if( repeat_check("ch1down",pwidth ) >= PWM_required_repeats ) then
                usb_shooting_mode = USB_IDLE                           -- set camera as waiting to shoot
                in_continuous_mode = false
            end
        end

        function ch2up(pwidth)
            if( repeat_check("ch2up",pwidth ) >= PWM_required_repeats ) then
                usb_shooting_mode = USB_SLEEP                          -- put camera into playback / sleep mode
                in_continuous_mode = false
            end
        end

        function ch2mid(pwidth)
            repeat_check("ch2mid",pwidth)
        --  if ( zoom_setpoint ~= nil ) then update_zoom(zoom_setpoint) else update_zoom(50) end
        end

        function ch2down(pwidth)
            repeat_check("ch2down",pwidth)
        --  update_zoom(0)
        end

    -- << gentwire-USB2 routines end here>>

-- PWM code - gentwire or pixhawk

    function pwm_mode()
        local pw = get_usb_power(2) * usb_precision
        if ( usb_mode == USB_MODE_Pixhawk ) then                       -- pixhawk  ?
            if  pw > 0  then
                if     pw < 5  then pwm1(pw)
                elseif pw < 10 then pwm2(pw)
                elseif pw < 15 then pwm3(pw)
                elseif pw < 20 then pwm4(pw)
                else   repeat_check("invalid pulse",pw)
                end
            end
        elseif ( usb_mode == USB_MODE_GntWire ) then                   -- gentwireUSB2 ?
            if  pw > 0  then
                if   ((pw < 15) or (pw > 224)) then repeat_check("invalid pulse",pw)
                elseif pw < 45  then ch1up(pw)
                elseif pw < 75  then ch1mid(pw)
                elseif pw < 105 then ch1down(pw)
                elseif pw < 135 then ch2up(pw)
                elseif pw < 165 then ch2mid(pw)
                elseif pw < 195 then ch2down(pw)
                elseif pw < 225 then repeat_check("idle pulse",pw)
                end
            end
        end
    end

--  ========================== Exposure Calculation =================================

-- Basic exposure calculation using shutter speed and ISO only
--   called for Tv-only and ND-only cameras (cameras without an iris)
function basic_tv_calc()
    tv96setpoint = tv96target
    av96setpoint = nil
    local min_av = get_prop(props.MIN_AV)
 -- calculate required ISO setting
    sv96setpoint = tv96setpoint + min_av - bv96meter
 -- low ambient light ?
    if (sv96setpoint > sv96max2 ) then                                 -- check if required ISO setting is too high
        sv96setpoint = sv96max2                                        -- clamp at max2 ISO if so
        tv96setpoint = math.max(bv96meter+sv96setpoint-min_av,tv96min) -- recalculate required shutter speed down to Tv min
 -- high ambient light ?
    elseif (sv96setpoint < sv96min ) then                              -- check if required ISO setting is too low
        sv96setpoint = sv96min                                         -- clamp at minimum ISO setting if so
        tv96setpoint = bv96meter + sv96setpoint - min_av               -- recalculate required shutter speed and hope for the best
    end
end


-- Basic exposure calculation using shutter speed, iris and ISO
--   called for iris-only and "both" cameras (cameras with an iris & ND filter)
function basic_iris_calc()
    tv96setpoint = tv96target
    av96setpoint = av96target
 -- calculate required ISO setting
    sv96setpoint = tv96setpoint + av96setpoint - bv96meter
 -- low ambient light ?
    if (sv96setpoint > sv96max1 ) then                                 -- check if required ISO setting is too high
        sv96setpoint = sv96max1                                        -- clamp at first ISO limit
        av96setpoint = bv96meter + sv96setpoint - tv96setpoint         -- calculate new aperture setting
        if ( av96setpoint < av96min ) then                             -- check if new setting is goes below lowest f-stop
            av96setpoint = av96min                                     -- clamp at lowest f-stop
            sv96setpoint = tv96setpoint + av96setpoint - bv96meter     -- recalculate ISO setting
            if (sv96setpoint > sv96max2 ) then                         -- check if the result is above max2 ISO
                sv96setpoint = sv96max2                                -- clamp at highest ISO setting if so
                tv96setpoint = math.max(bv96meter+sv96setpoint-av96setpoint,tv96min)  -- recalculate required shutter speed down to tv minimum
            end
        end
 -- high ambient light ?
    elseif (sv96setpoint < sv96min ) then                              -- check if required ISO setting is too low
        sv96setpoint = sv96min                                         -- clamp at minimum ISO setting if so
        tv96setpoint = bv96meter + sv96setpoint - av96setpoint         -- recalculate required shutter speed
        if (tv96setpoint > tv96max ) then                              -- check if shutter speed now too fast
            tv96setpoint = tv96max                                     -- clamp at maximum shutter speed if so
            av96setpoint = bv96meter + sv96setpoint - tv96setpoint     -- calculate new aperture setting
            if ( av96setpoint > av96max ) then                         -- check if new setting is goes above highest f-stop
                av96setpoint = av96max                                 -- clamp at highest f-stop
                tv96setpoint = bv96meter + sv96setpoint - av96setpoint -- recalculate shutter speed needed and hope for the best
            end
        end
    end
end

-- calculate exposure for cams without adjustable iris or ND filter
function exposure_Tv_only()
    insert_ND_filter = nil
    basic_tv_calc()
end

-- calculate exposure for cams with ND filter only
function exposure_NDfilter()
    insert_ND_filter = false
    basic_tv_calc()
    if (tv96setpoint > tv96max ) then                                  -- check if shutter speed now too fast
        insert_ND_filter = true                                        -- flag the ND filter to be inserted
        bv96meter = bv96meter - nd96offset                             -- adjust meter for ND offset
        basic_tv_calc()                                                -- start over, but with new meter value
        bv96meter = bv96meter + nd96offset                             -- restore meter for later logging
    end
end

-- calculate exposure for cams with adjustable iris only
function exposure_iris()
    insert_ND_filter = nil
    basic_iris_calc()
end

-- calculate exposure for cams with both adjustable iris and ND filter
function exposure_both()
    insert_ND_filter = false                                           -- NOTE : assume ND filter never used automatically by Canon firmware
    basic_iris_calc()
    if (tv96setpoint > tv96max ) then                                  -- check if shutter speed now too fast
        insert_ND_filter = true                                        -- flag the ND filter to be inserted
        bv96meter = bv96meter - nd96offset                             -- adjust meter for ND offset
        basic_iris_calc()                                              -- start over, but with new meter value
        bv96meter = bv96meter + nd96offset                             -- restore meter for later logging
    end
end

--  ========================== Main Program =================================

set_console_layout(1 ,1, 45, 14 )

printf("KAP 3.8 started - press MENU to exit")
bi=get_buildinfo()
lprintf("%s %s-%s %s %s %s", bi.version, bi.build_number, bi.build_revision, bi.platform, bi.platsub, bi.build_date)
chdk_version= tonumber(string.sub(bi.build_number,1,1))*100 + tonumber(string.sub(bi.build_number,3,3))*10 + tonumber(string.sub(bi.build_number,5,5))
if ( tonumber(bi.build_revision) > 0 ) then
    build = tonumber(bi.build_revision)
else
    build = tonumber(string.match(bi.build_number,'-(%d+)$'))
end

if ((chdk_version<130) or ((chdk_version==130)and(build<3810))) then
    printf(" Please update to CHDK 1.3 build 3810 or higher")
else
    if( props.CONTINUOUS_AF == nil ) then caf=-999 else caf = get_prop(props.CONTINUOUS_AF) end
    if( props.SERVO_AF == nil ) then saf=-999 else saf = get_prop(props.SERVO_AF) end
    if( props.ISO_MODE == nil ) then iso_mode= -999 else iso_mode= get_prop(props.ISO_MODE) end
    cmode = capmode.get_name()
    lprintf("Mode:%s,Continuous_AF:%d,Servo_AF:%d Drive:%d", cmode,caf,saf,drive_mode)
    lprintf(" Tv:"..print_tv(tv96target).." max:"..print_tv(tv96max).." min:"..print_tv(tv96min).." ecomp:"..(ec96adjust/96).."."..(math.abs(ec96adjust*10/96)%10) )
    lprintf(" Av:"..print_av(av96target).." minAv:"..print_av(av96minimum).." maxAv:"..print_av(av96max) )
    lprintf(" ISOmin:"..print_sv(sv96min).." ISO1:"..print_sv(sv96max1).." ISO2:"..print_sv(sv96max2) .." M:"..iso_mode)
    lprintf(" Focus:"..sd_ovr_mode_str.."  Video:"..video_mode.." USB:"..usb_mode..":"..usb_precision.." Tmo:"..script_timeout/60000)
    lprintf(" AvM:"..Av_mode.." int:"..(interval/1000).." Shts:"..max_shots.." Dly:"..start_delay.." B/L:"..backlight_saver)
    if ( iso_mode~=0) then printf("Warning : camera ISO not in AUTO mode") end
    sleep(500)

    -- delay shooting if so requested
        if (start_delay > 0 ) then
            printf("entering start delay of ".. start_delay.." seconds")
            sleep(2000)
            if (backlight_saver>0) then set_lcd_display(0) end
            sleep( start_delay*1000 )
            if (backlight_saver>0) then set_lcd_display(1) end
        end

    -- disable script exit via the shutter button
       set_exit_key("no_key")
       set_draw_title_line(0)

    -- enable high speed USB for USB PWM mode
        if ((usb_mode == USB_MODE_GntWire  ) or (usb_mode == USB_MODE_Pixhawk)) then
            flush_usb_buffers()
            set_remote_timing(usb_precision*1000)                      -- enable high precision pulse measurements
        end

    -- enable USB remote modes
        if (usb_mode > USB_MODE_None) then
            old_remote_mode = get_config_value(cfg1.remote_enable)
            set_config_value(cfg1.remote_enable,1)                     -- make sure USB remote is enabled
            set_config_value(cfg2.override_disable,1)
            sleep(1000)
            if ( wait_for_usb_active() == false) then                  -- can we start ?
                printf("Menu key exit request")
                restore()
                return
            else
                printf("USB start signal received")
                usb_shooting_mode = USB_SHOOTING
            end
            flush_usb_buffers()
        end

    -- switch to shooting mode
        switch_mode(1)
        update_zoom(zoom_setpoint)
        lock_focus()

    -- disable flash and AF assist lamp
        set_prop(props.FLASH_MODE, 2)                                  -- disable built-in flash
        set_prop(props.AF_ASSIST_BEAM,0)                               -- AF assist off if supported for this camera
        set_config_value( cfg2.console_timeout, 60)                    -- set console timeout to 60 seconds

    -- setup misc variables and configs
        script_exit = false
        if( get_video_button() == 1) then video_button = true else video_button = false end
        set_console_layout(2 ,1, 45, 5 )
        write_log_to_disk()

    -- sync the tic timer to the RTClock
        old_seconds = get_day_seconds()
        repeat until get_day_seconds() ~= old_seconds
        sync_tic = get_tick_count()
        next_shot_time = sync_tic
        usb_sleep_timer = get_tick_count() + usb_timeout

  -- main shooting loop
    repeat
        -- process USB PWM commands if enabled and not shooting continuous with a pixhawk
        if ((usb_mode == USB_MODE_GntWire) or ((usb_mode == USB_MODE_Pixhawk) and (in_continuous_mode == false))) then pwm_mode() end

        -- check if it's time to shoot?
        if (usb_mode == USB_MODE_OneShot) then new_usb_pulse = (get_usb_power(2) > 0) else new_usb_pulse = true end
        if (    (in_continuous_mode == true)                                                    -- immediate if continuous shooting has started and not using USB one shot mode
            or ((usb_mode <  USB_MODE_OneShot ) and (next_shot_time <= get_tick_count()))      -- based on intervalometer timing only (timing not under USB control)
            or ((usb_mode == USB_MODE_OneShot ) and (new_usb_pulse == true))                   -- next shot each time a USB pulse received
            or ((usb_mode >  USB_MODE_OneShot ) and (usb_shooting_mode == USB_SHOOTING))) then -- next shot if PWM sets usb_shooting_mode to 2

            -- intervalometer timing
            next_shot_time = next_shot_time + interval                          -- set time of next shot
            if( new_usb_pulse == true ) then
                usb_sleep_timer = get_tick_count() + usb_timeout                -- reset USB sleep timer
            end

            bshot = 0
            bracket_offset = 0
            repeat
                bshot = bshot + 1
                -- recalculate exposure when not in currently shooting in continuous mode
                if ( in_continuous_mode == false ) then

                    -- set focus at infinity if requested (maybe redundant for AFL & MF mode but makes sure it's set right)
                    if (focus_at_infinity ~= 0) then
                        set_focus(infx)
                        sleep(100)
                    end

                    -- check exposure if not taking bracketing shots
                    if ( bshot == 1 ) then
                        press("shoot_half")
                        wait_timeout(get_shooting, true, 2000, 50, "Warning : unable to focus / set exposure")
                        bv96raw=get_bv96()                                      -- get meter reading values (and add in exposure compensation)
                        tv96meter=get_tv96()
                        av96meter=get_av96()
                        sv96meter=get_sv96()
                    end
                    bv96meter=bv96raw-ec96adjust+bracket_offset

                    -- set minimum Av to larger of user input or current minimum for zoom setting
                    av96min= math.max(av96minimum,get_prop(props.MIN_AV))
                    if (av96target < av96min) then av96target = av96min end

                    -- calculate required setting for current ambient light conditions
                    if       (Av_mode == 1) then exposure_iris()
                    elseif   (Av_mode == 2) then exposure_NDfilter()
                    elseif   (Av_mode == 3) then exposure_both()
                    else                         exposure_Tv_only()
                    end

                    -- set up all exposure overrides
                    set_tv96_direct(tv96setpoint)
                    set_sv96(sv96setpoint)
                    if( av96setpoint ~= nil) then set_av96_direct(av96setpoint) end

                    if(Av_mode > 1) and (insert_ND_filter == true) then         -- ND filter available and needed?
                        set_nd_filter(1)                                        -- activate the ND filter
                        nd_string="NDin"
                    else
                        set_nd_filter(2)                                        -- make sure the ND filter does not activate
                        nd_string="NDout"
                    end
                    new_exposure=true
                    pwm_halted=false
                else
                    new_exposure=false
                end

                -- shoot !!
                ecnt=get_exp_count()
                hook_shoot.set(10000)                                           -- set the hook just before shutter release for timing
                press('shoot_full')                                             -- and finally shoot the image
                wait_timeout(hook_shoot.is_ready, true, 2000, 10, "timeout on hook_shoot.is_ready")  -- wait until the hook is reached

                if (in_continuous_mode == true) and (usb_mode == USB_MODE_Pixhawk) then -- if in continuous mode with pixhawk then wait for PWM command to proceed
                    flush_usb_buffers()
                    if not wait_for_shoot_pulse(5000) then
                        printf("no PWM shoot signal - halting shooting")
                        pwm_halted = true                                       -- drop out of continuous shooting mode if timeout
                    end
                end

                if (usb_shooting_mode==USB_SHOOTING) then                       -- indicate a PWM initiated single shotrequest has been processed
                    usb_shooting_mode = USB_IDLE
                end

                shot_tick = get_tick_count()                                    -- record actual start time as precisely as possible
                shot_time = os.time()
                if ( sync_led > 0 ) then set_led(sync_led-1,1) end
                hook_shoot.continue()                                           -- allow shooting to proceed

                -- wait for shot to complete
                if (interval > 0) then                                          -- normal shot or continuous?
                    if ( bracketing == 0 ) or (bshot == 3 ) then                -- bracketing off or this is the third shot ?
                        release('shoot_full')                                   -- release shoot full and shoot half for normal shots
                        wait_timeout(get_shooting, false, 6000, 10, "timeout after shoot full")
                    else
                        release('shoot_full_only')
                        local timestamp = get_tick_count() + 5000
                        repeat sleep(20) until ((get_exp_count()~=ecnt) or (get_tick_count() > timestamp))
                    end
                    in_continuous_mode = false
                else                                                             -- continuous mode (interval=0)
                    if pwm_halted == true then
                        release('shoot_full')
                        in_continuous_mode = false
                    else
                        if (drive_mode ~=1 ) then
                            release('shoot_full_only')                           -- else release shoot full (but not shoot half) if not in Canon continuous mode
                        end
                        in_continuous_mode = true
                    end
                    local timestamp = get_tick_count() + 5000
                    local led_timer = LED_BLINK_TIME
                    repeat 
                        sleep(20) 
                        if (sync_led>0 and led_timer>0) then                      -- turn off sync LED if time exceeds limit (will be reset below otherwise)
                            led_timer=led_timer-20
                            if ( led_timer<=0) then 
                                set_led(sync_led-1,0) 
                            end
                        end
                    until ((get_exp_count()~=ecnt) or (get_tick_count() > timestamp))
                end

                if ( sync_led >  0) then set_led(sync_led-1,0) end

                -- update shooting statistic and log as required
                shot_count = shot_count + 1
                shot_focus=get_focus()
                if(shot_focus ~= -1) and (shot_focus < 20000) then
                    focus_string=" foc:"..(shot_focus/1000).."."..(((shot_focus%1000)+50)/100).."m"
                    if(focus_at_infinity ~= 0) then
                        error_string="   **WARNING : focus not at infinity**"
                    end
                else
                    focus_string=" foc:infinity"
                    error_string=nil
                end

                msec_time_stamp = os.date("%Y%b%d %X",shot_time)..string.format(".%03d ", (shot_tick-sync_tic)%1000)
                printf(string.format('%d) IMG_%04d.JPG',shot_count,get_exp_count()))
                msec_time_stamp = nil
                if ( new_exposure == true ) then                            -- not in continuous mode ?
                    printf(" meter : Tv:".. print_tv(tv96meter)   .." Av:".. print_av(av96meter)   .." Sv:"..print_sv(sv96meter).." "..bv96raw ..":"..bv96meter)
                    printf(" actual: Tv:".. print_tv(tv96setpoint).." Av:".. print_av(av96setpoint).." Sv:"..print_sv(sv96setpoint).." Temp:"..get_temperature(0))
                    printf("         AvMin:".. print_av(av96min).." NDF:"..nd_string..focus_string)
                end

                if bshot == 1 then bracket_offset = bracketing else bracket_offset = -1*bracketing end

             until ((interval == 0) or (bracketing == 0) or (bshot == 3))

            -- is it time to insert a video sequence ?
            if ((video_mode>0) and (shot_count>1) and (shot_count%video_mode == 0)) then
                shoot_video()
            end
            collectgarbage()
        end

        -- write the log buffer to disk once a minute or when buffer gets too big and not in continuous mode
        if (     (( in_continuous_mode == false )      or (string.len(log_custom_buffer)>50000))
             and ((get_tick_count() >= log_write_time) or (string.len(log_custom_buffer)>10000)) ) then
            write_log_to_disk()
        end

        -- if USB control enabled and no activity (or a pause is requested) then idle in playback mode until MENU key pressed or USB activity
        if (   ((usb_mode == USB_MODE_On_Off) and (get_usb_power(1) == 0))
            or ((usb_mode >  USB_MODE_On_Off) and (usb_timeout>0) and (get_tick_count() > usb_sleep_timer ))
            or ((usb_mode >  USB_MODE_OneShot) and (usb_shooting_mode == USB_SLEEP )) )
        then
            in_continuous_mode = false                                 -- force refocus & exposure set on next pass after USB releases
            release('shoot_full')                                      -- release both half-press & full-press bits
            sleep(1000)
            unlock_focus()
            switch_mode(0)
            printf("USB halt requested")
            write_log_to_disk()
            wait_for_usb_active()
            usb_shooting_mode = USB_SHOOTING
            printf("USB halt finished")
            switch_mode(1)
            lock_focus()
            sleep(100)
            usb_sleep_timer = get_tick_count() + usb_timeout
        else
            wait_click(50)                                             -- otherwise check for any key presses
        end

        -- allow user to manually advance the next shot time by a full shutter press
        if is_key("shoot_full") then next_shot_time = get_tick_count()-1 end

        -- re-enable the LCD on any key press
        if( not(is_key("no_key")) and not(is_key("remote")) and (backlight_saver>0) and (blite_timer==0)) then
            set_lcd_display(1)
            blite_timer=get_tick_count()+10000
        end

        -- process display off timing
        if ((backlight_saver>0) and (blite_timer > 0 ) and (get_tick_count() >= blite_timer)) then
            set_lcd_display(0)
            blite_timer = 0
        end

        -- update display with any error message or the exit message if not
        if( error_string == nil) then
            error_string = " Press MENU to Exit."
            if( in_continuous_mode == true ) then
                 error_string = error_string .. " Shooting:Continuous "
            else
                if (usb_mode < USB_MODE_OneShot ) then
                     error_string = error_string .. "  Next shot:"..((next_shot_time - get_tick_count())/1000)
                end
            end
        end
        draw_message_string(error_string)
        error_string = nil

        -- script exit if menu key pressed
        if ( is_key("menu") ) then
            printf("MENU key pressed.")
            script_exit = true
        end

        -- script exit if menu shot count limit reached
        if ((max_shots>0) and (shot_count >= max_shots)) then
            printf("Total shots count reached.")
            script_exit = true
        end

        --  script exit if timeout
        if ( (script_timeout > 0) and (script_timeout < get_tick_count())) then
            printf("Script time-out reached.")
            script_exit = true
        end

    until (script_exit==true)

    printf("script halt requested")
    draw_message_string("Script halt - please wait")

    if( in_continuous_mode == true ) then
        release('shoot_full')                                          -- release both half-press & full-press bits
        hook_shoot.continue()                                          -- release hook just in case we got there
        wait_timeout(get_shooting, false, 2000, 10, "timeout releasing shoot full")
    end

    restore()
end

   --[[ end of file ]]--


