# Project Freezer Burn

This is a collaborative project by the Norse IoT club.

The project goals and deliverables are outlined at <https://scrum.norseiot.club/project/1/overview>.

Our collaborative scrum board is available at <https://scrum.norseiot.club/board/1>.

Feel free to discuss this project [on Discord](https://discord.com/channels/1027698639172288512/1145918385377525840).

## Contributing

This is the general workflow to make a contribution to this repository:

1. [Clone the repository](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository)
    - If you've already cloned the repository, it helps to do pull the most recent changes (e.g. `git checkout main && git pull`) to reduce conflicts when you merge your feature.
2. Make a feature branch
    - Every feature you develop will be coordinated in a ["feature branch"](https://blog.mergify.com/feature-branch-a-quick-walk-through-git-workflow/), so that features may be developed independently.
    - We will name all features "`feature/your-feature-name`" (all lowercase, [kebab-case](https://en.wikipedia.org/wiki/Letter_case#Kebab_case)) to distinguish features from hotfixes (e.g. `hotfix/oops-i-made-a-mistake`) and other types of branches.
    - We will merge feature branches directly into `main`.
3. ⭐ **Do your work** and [make your commits](https://github.com/git-guides/git-commit). ⭐
    - When developing, make sure to commit your changes regularly. We can always squash commits later, so don't worry about making too many commits. Do worry about losing work, or making it difficult for others to collaborate because you haven't shared your work.
4. Submit a [pull request (PR)](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests)
    - After you add changes to a topic branch or fork, you can open a pull request to ask your collaborators or the repository administrator to review your changes before merging them into the project.
5. [Request a review for your PR](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/requesting-a-pull-request-review)
    - Requesting a review from other contributors ensures that everyone is on the same page, and that others have the opportunity to point out improvements or changes you might consider.
6. (optional) [Address any merge conflicts](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/addressing-merge-conflicts/resolving-a-merge-conflict-on-github)
7. Merge your PR

### Example CLI usage

If you're looking to contribute via the git CLI, I've translated the above steps into commands. You can also use a [git GUI](https://desktop.github.com) if that's easier for you.

1. `git clone https://github.com/Norse-IoT/FreezerBurn.git` (or `gh repo clone Norse-IoT/FreezerBurn` if you have the GitHub CLI installed)
2. ```bash
    git checkout main # start feature branches on main
    git pull # start feature branches with the most recent updates
    git checkout -b 'feature/your-feature-name' # create a feature branch
    ```
3. ```bash
   # do this as many times as you need:
   git add -A # add all changes
   git commit -m "changed XYZ" # write a good git message
   ```
4. ```bash
   git push --set-upstream origin 'feature/your-feature-name'
   ```
5. (done from github)
6. (done from github)
7. (done from github)

Thanks! Feel free to reach out if you have any questions.

