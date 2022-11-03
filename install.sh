pacman -Syy
pacman -S xorg xorg-xinit xorg-server i3-gaps alacritty polybar ttf-dejavu ttf-fira-code noto-fonts-cjk ttf-font-awesome
mv ~/config/i3 ~/.config/i3
mv ~/config/polybar ~/.config/polybar
mv ~/config/Pictures ~/Pictures
mv ~/config/.xinitrc ~/xinitrc
mv ~/config/.bashrc ~/.bashrc
mv ~/config/.asoundrc ~/.asoundrc
rm -rf ~/config
echo "Done."
