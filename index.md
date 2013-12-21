---
layout: main
title: SRE
---

SRE is an experimental rendering/graphics engine built on OpenGL.

The Git repository can be accessed using `git ssh://git@sumbeard.net/sre`

<ul>
  {% for post in site.posts %}
    <li>
      <a href="{{ post.url }}">{{ post.date | date_to_string }} {{ post.title }}</a>
        <p>{{ post.excerpt }}</p>
    </li>
  {% endfor %}
</ul>