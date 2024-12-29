# Programming 1 final project - Hotel Management System

Completely written in C.

the project is meant to be for hotel staff.

## Features
- Log-In for system users (hotel staff)
- Make a new reservation and ensuring that all information are valid
- Check-In and updating the reservation status to Confirmed
- Check-Out if the reservation is Confirmed
- Cancel reservation (if the reservation status is unconfirmed)
- Edit reservation (if the reservation status is unconfirmed)
- Track room availability
- Query on reservations or rooms
- Reservation report by a specific date
- Reads and writes on text files
- Always asks if you wan't to save the changes to the system (text file)

## Instructions
- The program won't run without both rooms.txt, users.txt in the same directory of the program
- It always saves any changes in the text files: rooms.txt, reservations.txt.
- When doing a new reservation, it's status is unconfirmed, to confirm the reservation you must check-in first, but you can't check-in if the reservation date is not due yet
- Also you can edit a reservation or cancel it, but those can't be done on a confirmed reservation, if you want to cancel or edit, the reservation must be unconfirmed.
- After you check in and confirm your reservation, you can check out at any time, you can't check out on an unconfirmed reservation.

## Contributors
[Ahmed Rabie](https://github.com/JustAhmedRabie)

[Akrm Saad](https://github.com/kengit1)

[Mohamed Hany](https://github.com/mohany606)

[Amle Gomaa](https://github.com/AmleGomaa)

[Menna Shiref](https://github.com/mennashiref)
