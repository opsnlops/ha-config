
Hello! My name is April White, and I'm an engineer, but not the cool kind that drives trains. I do computer stuff.

I'm also looking for a new job, and I'm trying my best to break into a new field. It's nerve-wracking after working in one field for my entire career, but I'm ready for something new.

There's a little gap between magic and technology. It's the gap where you're not sure if something is magic of not. For children this gap is really big, but as we get older it gets smaller and smaller. (And that's really sad.) I strive to always live in that gap, as fleeting as it can be.

I want to go work in a field that allows me to work with other people that believe the same thing, and do our best to use our imagination to engineer things that make the gap just a little bit wider. 💜

## About me

I'm a Staff Engineer at MongoDB. I work on the Developer Productivity team, and as someone that's worked in operations (now called SRE, I get a new title every decade but the job stays the same) my whole career it's my job to make sure our teams are using best practices when it comes to building stable and observable systems.

I live on Whidbey Island in Washington, which is northwest of Seattle. As the crow flies I'm around 20 miles from Seattle, but it takes forever to get there because there's a boat involved.

I really love computers. I love everything about them. Fixing them, telling them what to do (aka coding), learning new things about them, and trying to use them in ways that they aren't suppose to be used. I basically spend all day messing with a computer, from the moment I get to work in the morning until it's time for bed. My laptop is never more than a few feet from me.

I'm also really, really into rabbits.

## What I want to do

I'm really into animatronics and their control systems. This website is my portfolio, and it showcases some of the stuff I've built. I want to work on anything related to that field. You can even give me the boring jobs that no one else wants to do because it'll all be new to me.

I jokingly tell people "Yeah I'm that person that went to the Tiki Room at Disneyland and said 'Wow, this is so cool, I wish I had this at home,' only unlike nearly everyone else, I'm most of the way there."

## Things I've taught myself

I have developed a stack of software (and hardware) for controlling animatronics. I did this because when I was first starting out I couldn't find anything that I liked that worked on Macs, so I decided I'd learn and make it myself. My stubbornness has really paid off, because I've learned a lot of stuff along the way.

### Real time control system

The heart of my system is something I call the "Creature Server." It's written in C++ and runs on Linux and macOS. (The server itself is Linux.) It's actually pretty simple, it's mostly an event loop that runs every one millisecond and performs whatever actions need to happen in that frame. Once it's done, it goes to sleep, ready to pounce again on the next timeslice.

The server talks to my characters over e1.31, which is DMX over multicast UDP. I picked this because it's really lightweight and scales as big as I want it to. Each DMX frame has 512 channels, so I give each character an offset into this array to know what to do. They need less than 10 channels, so I can run a flock of 50ish birds off a single 512 byte packet. (The motion frames are spaced at 20ms since I'm making motors move. There's no need to be more precise than that.)

Each character runs two pieces of software I wrote.

One piece runs on a Linux machine. Usually a Raspberry Pi because they're cheap and have wired Ethernet. It's what's listening for the e1.31 frames. It's written in C++ as well, and maintains a websocket back to the server for non-real time communication of things like status messages.

The other piece runs on some custom hardware I've designed using the Pi Pico platform. That application is written in pure C, and is designed to be as real time as I can get on a Pi Pico. It's event loop is locked at a perfect 50Hz (20ms). It'll get a motion frame from the Linux machine, and then at the clock tick adjust the PWM timers to match. That's what actually makes the characters move.

Audio is handled via HDMI (since there's a lot of channels available) and nothing more than an A/V receiver. I didn't even buy one, it's a hand-me-down from what used to be in my living room. Each character gets its own speaker, and the server plays audio files at the exact right time in sync with the motion data. I was looking at a Pi, remembered it has an HDMI port, got curious, and turns out it was possible. 🎉

So that's how playback is handled! I've had to re-write it all two or three times because each time I realize I've done things the hard way and I want another shot at making it better. I'm really happy with where I've landed.

### Programming

Having a way to play back animations is cool, but it's not meaningful without a way to write the animations!

To do this I wrote a macOS application (that also works on iOS) that I can use to create and stage animations. I call it the "Creature Console" because that's basically what it is.

It'll use any USB or Bluetooth joystick that's connected to the host. I've collected a lot of joysticks over the last few years, just because I want to experiment and find what I like best.

In the end I ended up designing my own joystick that's more purpose-built to programming animatronics. It's also based on the Pi Pico platform, but what makes it special is that joysticks themselves have three axises (left/right, up/down, and twist), which work really well for things like a character's head. I also bought some 75mm sliding pots that I use for things like making a bird lean.

I thought I was getting carried away when I went so far as to make a joystick that was purpose built for this, but then I saw an old video showing that the original engineers on the Tiki Room had to do the same thing, so I figured it was okay. (I am so impressed with those folks! They had mad skills!)

My macOS app can be used for both live control and recording. Live control is handled in "streaming mode," where it's sending motion data to the server over a simple websocket. The server then gets these frames, schedules them in it's event loop, and the process kicks off.

But one really fun thing is that I wrote the app to also work on iOS, and you can pair Bluetooth joysticks with iPhone. This gives me the power to basically walk around with my phone in my pocket while holding a joystick in my hands and control a creature super discreetly. It's a fun way to make things seem magical to other people.

### Character design

And lastly, when I'm making something new, I come up with the character first, and then design the technology around it. In the end I'm trying to tell a story, and the tech is a tool to tell it with. It's not the other way around. The tech should fade into the background and the character should shine. That's what's most important of all!


## Reality check

I know I have a long ways to go before I can call myself an expert in the field of animatronics. I'm entirely self-taught, even if it is with an education in Computer Science and a few decades of experience in the tech industry behind me.

I know I don't fit the mold for what you're usually looking for. I didn't go to school for this. But it's something I really want and I'm hungry to do.

I know I can't go from being a Staff Engineer in one field to another. I know I'll need to take some steps backwards, and I'm okay with that. Having a fresh set of challenges is something I really want to do.

I also know that this kind of work is hands-on. I know I'll have to move, and I'm also okay with that, too. I can't (and don't event want to) work remotely when I'm working with a team to build magic. We need to be together, and we need to have our hands on the things we're working on. I'm single, I don't have kids, and I don't even have any pets. Moving isn't a big deal, other than selling my current house.

Not being able to be hands-on with the stuff I'm working on is what's driving me. I am willing (and expecting) to take steps backwards in order to go into a field I really want to break into. The tech industry has moved to putting the computers in one central place (the cloud), and I'd get arrested if I went to go see them in person. I want to get back to being able to touch and smell the things I'm working on! (Well, as long as it doesn't smell like the magic blue smoke that powers electronics. 😅)

## Thanks for making it this far

Thanks so much for reading this! I know it was a lot. I have a lot of stories to tell, and I wanted to let you know how hard I've worked to learn a new field.

If you would like to speak with me, here's my LinkedIn profile, or you can email me at april@opsnlops.io. I really look forward to speaking with you, so don't hesitate to get in touch with me.

With many thanks,
April White 🐰💜🦜
