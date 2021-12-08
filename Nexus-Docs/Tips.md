# Tips for Presenting LifeHash Images

LifeHashes can improve the security of digital data in conjunection with other methods of inspection and hashing, but they must be presented well:

* **Don't** vignette or round the corners of a LifeHash image. Every pixel contributes to the security of the image, so show the image as a square. If you *really* want to round the corners, make the radius small enough to still show the corner pixels.
* **Don't** interpolate or blur a LifeHash image: show every pixel crisply. On iOS UIKit this is accomplished by setting `layer.magnificationFilter = .nearest` on a `UIImageView`. Under SwiftUI you call `myImage.interpolation(.none)`. The [Swift LifeHash library](https://github.com/BlockchainCommons/LifeHash) already does this for you.

Also, be sure you're optimizing your use of the library:

* The [Swift LifeHash library](https://github.com/BlockchainCommons/LifeHash) renders LifeHash images asynchronously and caches the result, so if you pass in the same fingerprint you'll get the same image back right away. If LifeHash rendering seems slow, be sure you're compiling the Release configuration of your target: LifeHash is *really fast* when compiled for Release.
