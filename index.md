---
layout: main
title: SRE
---

SRE is an experimental rendering/graphics engine built on OpenGL.

The repository is hosted on GitHub at <https://github.com/Sumbeard/sre>.

<ul>
  {% for post in site.posts %}
    <li>
      <a href="{{ site.baseurl}}{{ post.url }}">{{ post.title }} - {{ post.date | date_to_string }}</a>
        <p>{{ post.excerpt }}</p>
    </li>
  {% endfor %}
</ul>
